//
// Created by limo on 12/9/17.
//

#ifndef RAKEMAN_ENGINE_SORTUNSORTEDPOSTINGLISTTASK_H
#define RAKEMAN_ENGINE_SORTUNSORTEDPOSTINGLISTTASK_H


#include "task.h"

class CSortUnsortedPostingListTask : public ITask {
public:
    explicit CSortUnsortedPostingListTask(const std::string &term);

    int work() override;

    static std::shared_ptr<ITask> Deserialize(const std::string &);

public:
    std::string m_term;

};


#endif //RAKEMAN_ENGINE_SORTUNSORTEDPOSTINGLISTTASK_H
