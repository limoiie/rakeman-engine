//
// Created by limo on 11/29/17.
//

#include "redisdeport.h"

#include <common/serializer.h>
#include <common/integer2string.h>

#include <saker/postingsop.hpp>

const char *KEY_TM_DICT = "TEMP_DICTIONARY";
const char *KEY_HM_DICT = "HASH_DICTIONARY";

CRedisDeport::CRedisDeport(std::string host, size_t port)
        : m_host(std::move(host)), m_port(port), m_client(), m_state(UNCONNECTED) {
    // empty
}

bool CRedisDeport::connect() {
    // there can only be one thread to connect for each deport
    std::unique_lock<std::mutex> guard(m_mutex);
    // callback for listening to status changes of client
    auto cb = [this](const std::string& host, std::size_t port,
                     cpp_redis::client::connect_state status) {
        switch (status) {
            case cpp_redis::client::connect_state::dropped:
                m_state = DISCONNECTED;
                break;
            case cpp_redis::client::connect_state::start:
            case cpp_redis::client::connect_state::sleeping:
                m_state = CONNECTING;
                break;
            case cpp_redis::client::connect_state::ok:
                m_state = CONNECTED;
                break;
            case cpp_redis::client::connect_state::failed:
                m_state = UNCONNECTED;
                break;
            case cpp_redis::client::connect_state::lookup_failed:
                break;
            case cpp_redis::client::connect_state::stopped:
                m_state = UNCONNECTED;
                break;
        }
    };
    // the state can not be connecting since there could be only one thread
    // to connect at the same time, which means there is no other thread is
    // connecting.
    if (m_state == DISCONNECTED || m_state == UNCONNECTED)
        m_client.connect(m_host, m_port, cb);
    return m_state == CONNECTED;
}

bool CRedisDeport::disconnect() {
    if (m_client.is_connected())
        m_client.disconnect(true);
    m_state = DISCONNECTED;
    return true;
}

CRedisDeport::State CRedisDeport::connectState() {
    return m_state;
}

bool CRedisDeport::fetchPostings(const std::vector<std::string> &terms, PostingsMap &map) {
    PostingsMap map1, map2;
    if (__fetchPostingsInDict(terms, map1)) {
        if (__fetchPostingsInTemp(terms, map2)) {
            for (const auto &term : terms) {
                ConjunctLists(map1[term], map2[term], map[term]);
            }
            return true;
        }
    }
    return false;
}

bool CRedisDeport::fetchPostings(const std::vector<std::string> &terms, std::vector<std::list<PostingNode>> &nodes) {
    PostingsMap map;
    if (fetchPostings(terms, map)) {
        for (auto & term : terms)
            nodes.push_back(std::move(map[term]));
        return true;
    }
    return false;
}

bool CRedisDeport::storePostingsInDict(PostingsMap &map) {
    __assertConnected();

    std::string container;
    std::vector<std::pair<std::string, std::string>> key_value_pairs;
    for (auto & p : map) {
        size_t offset = 0;
        serialize(p.second, container, offset);
        key_value_pairs.emplace_back(p.first, container);
        container.clear();
    }

    // update term-postings pairs
    auto fut = m_client.hmset(KEY_HM_DICT, key_value_pairs);
    m_client.commit();

    if (!fut.get().ok()) {
        throw std::runtime_error("Failed to store postings!");
    }
    return true;
}

bool CRedisDeport::appendPostingsToTemp(PostingsMap &map) {
    __assertConnected();

    std::vector<std::string> terms;
    std::vector<std::future<cpp_redis::reply>> futures;

    // iterate each pair in map
    for (auto p : map) {
        terms.push_back(p.first);
        std::multimap<std::string, std::string> k_vs;
        for (auto i : p.second) {
            size_t offset = 0;
            std::string serialized_node;
            serialize(i, serialized_node, offset);
            k_vs.emplace(Integer2String(i.doc_id), serialized_node);
        }
        // append postings by term
        futures.push_back(m_client.zadd(p.first, {"CH"}, k_vs));
    }
    // insert added terms into set
    futures.push_back(m_client.sadd(KEY_TM_DICT, terms));

    m_client.commit();

    // wait and check the response
    for (auto & fut : futures) {
        auto reply = fut.get();
        if (reply.is_error()) {
            throw std::runtime_error("Failed to append postings!");
        }
    }
    return true;
}

bool CRedisDeport::deleteTermsInTemp(const std::vector<std::string> &keys) {
    __assertConnected();
    auto fut1 = m_client.del(keys);
    auto fut2 = m_client.srem(KEY_TM_DICT, keys);
    m_client.commit();
    if (!fut1.get().ok() || !fut2.get().ok()) {
        throw std::runtime_error("Failed to delete keys!");
    }
    return true;
}

bool CRedisDeport::deleteTermsInDict(const std::vector<std::string> &keys) {
    __assertConnected();
    auto fut = m_client.hdel(KEY_HM_DICT, keys);
    m_client.commit();
    if (!fut.get().ok()) {
        throw std::runtime_error("Failed to delete keys in hm!");
    }
    return true;
}

void CRedisDeport::__assertConnected() {
    if (m_state != CONNECTED)
        if (!connect())
            throw std::runtime_error("Connect redis failed!");
}

bool CRedisDeport::__fetchPostingsInTemp(const std::vector<std::string> &terms, PostingsMap &map) {
    std::vector<std::future<cpp_redis::reply>> futures;
    for (auto & term : terms) {
        futures.push_back(m_client.zrange(term, 0, -1, false));
    }
    m_client.commit();

    for (size_t i = 0; i < futures.size(); ++i) {
        auto reply = futures[i].get();
        if (reply.is_error())
            throw std::runtime_error("Failed to fetch postings in term!");
        auto &nodelist = map[terms[i]];

        const auto &replies = reply.as_array();
        for (auto &rep : replies) {
            if (!rep.is_null()) {
                size_t offset = 0;
                PostingNode node;
                deserialize(rep.as_string(), offset, node);
                nodelist.push_back(std::move(node));
            }
        }
    }
    return true;
}

bool CRedisDeport::__fetchPostingsInDict(const std::vector<std::string> &terms, PostingsMap &map) {
    auto fut = m_client.hmget(KEY_HM_DICT, terms);
    m_client.commit();

    auto reply = fut.get();
    if (reply.is_error())
        throw std::runtime_error("Failed to fetch Postings!");

    const auto &replies = reply.as_array();
    for (size_t i = 0; i < replies.size(); ++i) {
        if (!replies[i].is_null()) {
            size_t offset = 0;
            deserialize(replies[i].as_string(), offset, map[terms[i]]);
        }
    }
    return true;
}
