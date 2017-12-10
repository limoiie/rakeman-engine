//
// Created by limo on 12/8/17.
//

#ifndef RAKEMAN_ENGINE_BREAKDOCBLOCKTASK_H
#define RAKEMAN_ENGINE_BREAKDOCBLOCKTASK_H

#include <vector>
#include <memory>

#include "task.h"

class Doc;

class CBreakDocBlockTask : public ITask {
public:
    explicit CBreakDocBlockTask(task_id_t task_id, std::vector<Doc> docs);

    /**
     *
     * @return Work status, 0 for success
     */
    int work(ITaskQueue &queue) override;

    /**
     * Deserialize from string. TODO: consider replacing this with function
     */
    static std::shared_ptr<ITask> Deserialize(const std::string &);

private:
    /**
     * Documents going to be break and stored.
     */
    std::vector<Doc> m_docs;

};

#endif //RAKEMAN_ENGINE_BREAKDOCBLOCKTASK_H
