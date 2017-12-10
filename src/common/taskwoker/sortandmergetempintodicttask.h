//
// Created by limo on 12/9/17.
//

#ifndef RAKEMAN_ENGINE_SORTUNSORTEDPOSTINGLISTTASK_H
#define RAKEMAN_ENGINE_SORTUNSORTEDPOSTINGLISTTASK_H


#include "task.h"

class CSortAndMergeTempIntoDictTask : public ITask {
public:
    explicit CSortAndMergeTempIntoDictTask(task_id_t task_id, const std::string &term);

    int work(ITaskQueue &queue) override;

    static std::shared_ptr<ITask> Deserialize(const std::string &);

public:
    std::string m_term;

};


#endif //RAKEMAN_ENGINE_SORTUNSORTEDPOSTINGLISTTASK_H
