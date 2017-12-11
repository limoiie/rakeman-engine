//
// Created by limo on 12/11/17.
//

#ifndef RAKEMAN_ENGINE_QUERYEXPRESSTASK_H
#define RAKEMAN_ENGINE_QUERYEXPRESSTASK_H


#include "task.h"

class CQueryExpressTask : public ITask {
public:
    explicit CQueryExpressTask(task_id_t task_id, std::string query);

    int work(std::shared_ptr<ITaskQueue> &queue) override;

    static std::shared_ptr<ITask> Deserialize(const std::string &);

private:
    std::string m_query;

};

#endif //RAKEMAN_ENGINE_QUERYEXPRESSTASK_H
