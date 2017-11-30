//
// Created by limo on 11/29/17.
//

#include "redisdeport.h"

#include <utility>

#include <cppredis/includes/cpp_redis/core/reply.hpp>

CRedisDeport::CRedisDeport(std::string host, size_t port)
        : m_host(std::move(host)), m_port(port), m_client(),
          m_state(UNCONNECTED) {}

PostingsMap CRedisDeport::fetchPostings(std::vector<std::string> &terms) {
    if (m_state == CONNECTED) {
        std::vector<
                std::pair<std::string,
                        std::future<cpp_redis::reply>>
        > futures(terms.size());
        for (const auto &term : terms)
            futures.emplace_back(term, std::move(m_client.lrange(term, 0, -1)));
        m_client.commit();

        PostingsMap map;
        for (auto &fut : futures) {
            auto reps = fut.second.get();
            if (reps.is_error())
                throw std::runtime_error("Fetch failed from redis");
            auto &node_list = map[fut.first];
            for (const auto &rep : reps.as_array()) {
                node_list.push_back(PostingNode::deserialize(rep.as_string()));
            }
        }
        return map;
    }
    return nullptr;
}

bool CRedisDeport::storePostings(PostingsMap &map) {
    if (m_state == CONNECTED) {
        std::vector<std::string> nodes;
        std::vector<std::future<cpp_redis::reply>> reply_list;
        auto st_itr = map.begin();
        auto ed_itr = map.end();
        for (; st_itr != ed_itr; ++st_itr) {
            nodes.clear();
            for (const auto &node : st_itr->second)
                nodes.push_back(PostingNode::serialize(node));
            reply_list.push_back(std::move(m_client.rpush(st_itr->first, nodes)));
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
    return false;
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

State CRedisDeport::connectState() {
    return m_state;
}
