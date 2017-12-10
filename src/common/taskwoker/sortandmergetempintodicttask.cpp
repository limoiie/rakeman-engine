//
// Created by limo on 12/9/17.
//

#include <raker/docindexer.h>
#include <common/deport/deport.h>
#include <common/factory/deportfactory.h>
#include <common/factory/factoryfactory.h>
#include "sortandmergetempintodicttask.h"

CSortAndMergeTempIntoDictTask::CSortAndMergeTempIntoDictTask(task_id_t task_id, const std::string &term)
        : ITask(task_id, SORT_UNSORTED_POSTING_LIST),
          m_term(term) {
    // empty
}

std::shared_ptr<ITask> CSortAndMergeTempIntoDictTask::Deserialize(const std::string & str) {
    return std::make_shared<CSortAndMergeTempIntoDictTask>(str);
}

int CSortAndMergeTempIntoDictTask::work(ITaskQueue &queue) {
    auto deport = CFactoryFactory::getInstance()
            ->getDeportFactory()
            ->get(CFactory<IDeport>::DEFAULT);

    // step 1: fetch posting list by term
    PostingsMap nodelists;
    deport->fetchPostings({m_term}, nodelists);

    // step 2: store posting list by term
    deport->storePostingsInDict(nodelists);

    // step 3: delete terms in temp area: remove sorted set by term and terms in temp dict
    deport->deleteTermsInTemp(std::vector<std::string>{m_term});
    return 0;
}
