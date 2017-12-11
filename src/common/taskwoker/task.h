//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_TASK_H
#define RAKEMAN_ENGINE_TASK_H

#include <string>
#include <memory>

class ITaskQueue;

enum TaskType {
    BREAK_DOCUMENT_BLOCK,
    SORT_MERGE_POSTINGS,
    QUERY_EXPRESS
};

typedef long long int task_id_t;

class ITask {
public:
    explicit ITask(task_id_t task_id, TaskType type)
            : m_task_id(task_id),
              m_type(type) {}
    virtual ~ITask() = default;

    virtual int work(std::shared_ptr<ITaskQueue> &queue) = 0;

    static std::shared_ptr<ITask> Deserialize(const std::string &str);

protected:
    const task_id_t m_task_id;
    const TaskType m_type;

};

#endif //RAKEMAN_ENGINE_TASK_H
