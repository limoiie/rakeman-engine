//
// Created by limo on 12/8/17.
//

#include <common/factory/factoryfactory.h>

#include <utility>
#include "worker.h"

CWoker::CWoker(std::shared_ptr<ITaskQueue> task_queue)
        : m_queue(std::move(task_queue)),
          m_task_count(0),
          m_running(false) {
    // empty
}

void CWoker::operator()() {
    m_running = true;
    while (m_running) {
        m_queue->waitForPopTask()->work(m_queue);
        ++m_task_count;
    }
}

void CWoker::shutdown() {
    m_running = false;
    m_task_count = 0;
}


