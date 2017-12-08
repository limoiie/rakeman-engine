//
// Created by limo on 11/29/17.
//

#include "redisdeport.h"

#include <utility>

#include <cppredis/includes/cpp_redis/core/reply.hpp>

CRedisDeport::CRedisDeport(std::string host, size_t port)
        : m_host(std::move(host)), m_port(port), m_client(),
          m_state(UNCONNECTED) {}

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
    __assertConnected();

    std::vector<
            std::pair<const std::string &,
                    std::future<cpp_redis::reply>>
    > futures;
    for (const auto &term : terms)
        futures.emplace_back(term, m_client.lrange(term, 0, -1));
    m_client.commit();

    for (auto &fut : futures) {
        auto reps = fut.second.get();
        if (reps.is_error())
            throw std::runtime_error("Fetch failed from redis");
        auto &node_list = map[fut.first];
        for (const auto &rep : reps.as_array()) {
            node_list.push_back(PostingNode::Deserialize(rep.as_string()));
        }
    }
    return true;
}

bool CRedisDeport::fetchPostings(const std::vector<std::string> &terms, std::vector<std::list<PostingNode>> &nodes) {
    __assertConnected();

    std::vector<std::pair<int, std::future<cpp_redis::reply>>> futures;
    for (unsigned int i = 0; i < terms.size(); ++i)
        futures.emplace_back(i, m_client.lrange(terms[i], 0, -1));
    m_client.commit();

    nodes.resize(terms.size());

    for (auto &fut : futures) {
        auto reps = fut.second.get();
        if (reps.is_error())
            throw std::runtime_error("Fetch failed from redis");

        auto &node_list = nodes[fut.first];
        for (const auto &rep : reps.as_array()) {
            node_list.push_back(PostingNode::Deserialize(rep.as_string()));
        }
    }
    return true;
}

// todo: try to store postings in string not in list
bool CRedisDeport::storePostings(PostingsMap &map) {
    __assertConnected();

    std::vector<std::string> nodes;
    std::vector<std::future<cpp_redis::reply>> reply_list;
    auto st_itr = map.begin();
    auto ed_itr = map.end();
    for (; st_itr != ed_itr; ++st_itr) {
        nodes.clear();
        for (const auto &node : st_itr->second)
            nodes.push_back(PostingNode::Serialize(node));
        reply_list.push_back(m_client.rpush(st_itr->first, nodes));
    }
    m_client.commit();
    // wait for completing commands
    for (auto &rep : reply_list) {
        if (!rep.get().ok()) {
            throw std::runtime_error("Store failed from redis");
        }
    }
    return true;
}

// todo: try to store postings in string not in list
bool CRedisDeport::storePostings(const std::vector<std::string> &terms, std::vector<std::list<PostingNode>> &nodes) {
    __assertConnected();

    std::vector<std::string> serialized_nodes;
    std::vector<std::future<cpp_redis::reply>> reply_list;
    for (unsigned int i = 0; i < terms.size(); ++i) {
        for (const auto &node : nodes[i])
            serialized_nodes.push_back(PostingNode::Serialize(node));
        reply_list.push_back(m_client.rpush(terms[i], serialized_nodes));
        serialized_nodes.clear();
    }
    m_client.commit();
    // wait for completing commands
    for (auto &rep : reply_list) {
        if (!rep.get().ok()) {
            throw std::runtime_error("Store failed from redis");
        }
    }
    return true;
}

bool CRedisDeport::deleteKey(const std::vector<std::string> &keys) {
    __assertConnected();
    auto reply = m_client.del(keys);
    m_client.commit();
    if (reply.get().is_error()) {
        throw std::runtime_error("Failed to delete keys!");
    }
    return true;
}

void CRedisDeport::__assertConnected() {
    if (m_state != CONNECTED)
        if (!connect())
            throw std::runtime_error("Connect redis failed!");
}
