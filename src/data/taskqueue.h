//
// Created by limo on 12/8/17.
//

#ifndef RAKEMAN_ENGINE_TASKQUEUE_H
#define RAKEMAN_ENGINE_TASKQUEUE_H


#include <common/taskwoker/task.h>

class ITaskQueue {
public:
    // duplicated from %IDeport, consider to refactor
    enum State {
        DISCONNECTED,
        UNCONNECTED,
        CONNECTING,
        CONNECTED
    };

    virtual std::shared_ptr<ITask> waitForPopTask() = 0;
    virtual ~ITaskQueue() = default;

    // duplicated from %IDeport, consider to refactor
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual State connectState() = 0;

};

#endif //RAKEMAN_ENGINE_TASKQUEUE_H
