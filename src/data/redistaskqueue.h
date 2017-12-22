//
// Created by limo on 12/8/17.
//

#ifndef RAKEMAN_ENGINE_REDISTASKQUEUE_H
#define RAKEMAN_ENGINE_REDISTASKQUEUE_H

#include <cppredis/includes/cpp_redis/core/client.hpp>
#include "taskqueue.h"

// TODO: just copied from %CRedisDeport, consider refactoring
class CRedisTaskQueue : public ITaskQueue {
public:
    CRedisTaskQueue(const std::string &host, size_t port);

    std::shared_ptr<ITask> waitForPopTask() override;
    void pushResponse(task_id_t task_id, TaskType type, bool success, std::string response) override;

    bool connect() override;
    bool disconnect() override;
    State connectState() override;

private:
    void __assertConnected();

    // redis host
    std::string m_host;
    // redis port
    size_t m_port;
    // redis client for msg queue implement
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

#endif //RAKEMAN_ENGINE_REDISTASKQUEUE_H
