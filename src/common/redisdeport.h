//
// Created by limo on 11/29/17.
//

#ifndef RAKEMAN_ENGINE_REDISDEPORT_H
#define RAKEMAN_ENGINE_REDISDEPORT_H

#include "deport.h"

#include <cppredis/includes/cpp_redis/core/client.hpp>

class CRedisDeport : public IDeport {
public:
    explicit CRedisDeport(std::string host, size_t port);

    bool fetchPostings(std::vector<std::string> &terms, PostingsMap &map) override ;
    bool storePostings(PostingsMap &map) override;

    bool connect() override;
    bool disconnect() override;
    State connectState() override;

private:
    // redis host
    std::string m_host;
    // redis port
    size_t m_port;
    // redis client used to fetch and store things
    cpp_redis::client m_client;
    // connecting state:
    //  -1 for disconnected
    //   0 for unconnected
    //   1 for connecting
    //   2 for connected
    State m_state;
    // mutex
    std::mutex m_mutex;

};

#endif //RAKEMAN_ENGINE_REDISDEPORT_H
