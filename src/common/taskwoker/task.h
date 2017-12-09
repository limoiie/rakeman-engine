//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_TASK_H
#define RAKEMAN_ENGINE_TASK_H

#include <string>
#include <memory>

enum TaskType {
    BREAK_DOCUMENT_BLOCK,
    SORT_UNSORTED_POSTING_LIST,
};

class ITask {
public:
    explicit ITask(TaskType type) : m_type(type) {}
    virtual ~ITask() = default;

    virtual int work() = 0;

    static std::shared_ptr<ITask> Deserialize(const std::string &str);

protected:
    const TaskType m_type;

};

#endif //RAKEMAN_ENGINE_TASK_H
