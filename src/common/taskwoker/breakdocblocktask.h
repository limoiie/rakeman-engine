//
// Created by limo on 12/8/17.
//

#ifndef RAKEMAN_ENGINE_BREAKDOCBLOCKTASK_H
#define RAKEMAN_ENGINE_BREAKDOCBLOCKTASK_H

#include <data/doc.h>
#include <vector>
#include <memory>
#include "task.h"

class CBreakDocBlockTask : public ITask {
public:
    explicit CBreakDocBlockTask(std::vector<Doc> docs);

    /**
     *
     * @return Work status, 0 for success
     */
    int work() override;

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
