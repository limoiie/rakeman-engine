//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_WORKER_H
#define RAKEMAN_ENGINE_WORKER_H

#include <data/taskqueue.h>

class CWoker {
public:
    explicit CWoker(std::shared_ptr<ITaskQueue> task_queue);

    void operator()();
    void shutdown();

private:
    std::shared_ptr<ITaskQueue> m_queue;
    long long int m_task_count;
    bool m_running;

};


#endif //RAKEMAN_ENGINE_WORKER_H
