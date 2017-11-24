//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_TASK_H
#define RAKEMAN_ENGINE_TASK_H


enum TaskType {
    DOC_TOKENIZE
    // todo
};

class CTaskMeta {
    // todo
};


class ITask {
public:
    virtual int work() = 0;

    const TaskType type;

protected:
    ITask(TaskType type, int task_id) : type(type), m_task_id(task_id) {}

private:
    int m_task_id;

};


#endif //RAKEMAN_ENGINE_TASK_H
