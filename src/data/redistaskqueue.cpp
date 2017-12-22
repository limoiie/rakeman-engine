//
// Created by limo on 12/8/17.
//

#include <common/serializer.h>
#include <common/taskwoker/response.h>
#include <common/config.h>
#include "redistaskqueue.h"

CRedisTaskQueue::CRedisTaskQueue(const std::string &host, size_t port)
        : m_host(host), m_port(port), m_client(), m_state(UNCONNECTED) {
    // empty
}

std::shared_ptr<ITask> CRedisTaskQueue::waitForPopTask() {
    __assertConnected();

    // continue popping out of the queue until get one
    while (true) {
        // 0 means wait a task until forever
        auto fut = m_client.blpop(std::vector<std::string>{KEY_MSG_QUEUE}, 0);
        m_client.commit();
        auto rep = fut.get();
        if (rep.is_error()) {
            // TODO: here should be a log
            std::cout << "Failed to pop out of task queue! Continue to pop" << std::endl;
            continue;
        }
        return ITask::Deserialize(rep.as_array().back().as_string());
    }
}

void CRedisTaskQueue::pushResponse(task_id_t task_id, TaskType type, bool success, std::string response) {
    __assertConnected();

    Response(m_client, task_id, type, success, response);
}

bool CRedisTaskQueue::connect() {
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

bool CRedisTaskQueue::disconnect() {
    if (m_client.is_connected())
        m_client.disconnect(true);
    m_state = DISCONNECTED;
    return true;
}

ITaskQueue::State CRedisTaskQueue::connectState() {
    return m_state;
}

void CRedisTaskQueue::__assertConnected() {
    if (m_state != CONNECTED)
        if (!connect())
            throw std::runtime_error("Connect redis failed!");
}
