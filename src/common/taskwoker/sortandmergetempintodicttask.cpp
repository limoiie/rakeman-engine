//
// Created by limo on 12/9/17.
//

#include "sortandmergetempintodicttask.h"

#include <raker/docindexer.h>
#include <common/deport/deport.h>
#include <common/factory/deportfactory.h>
#include <common/factory/factoryfactory.h>
#include <data/taskqueue.h>
#include <common/serializer.h>
#include <common/log.h>

CSortAndMergeTempIntoDictTask::CSortAndMergeTempIntoDictTask(task_id_t task_id, const std::string &term)
        : ITask(task_id, SORT_MERGE_POSTINGS),
          m_term(term) {
    // empty
}

std::shared_ptr<ITask> CSortAndMergeTempIntoDictTask::Deserialize(const std::string & str) {
    size_t offset = 0;
    task_id_t task_id;
    std::string term;

    // step 1: fetch the count of docs
    deserialize(str, offset, task_id);
    deserialize(str, offset, term);

    limo::log_merge_task(task_id, term);
    return std::make_shared<CSortAndMergeTempIntoDictTask>(task_id, term);
}

int CSortAndMergeTempIntoDictTask::work(std::shared_ptr<ITaskQueue> &queue) {
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

    // step 4: response
    queue->pushResponse(m_task_id, SORT_MERGE_POSTINGS, true, "");

    limo::log_merge_response(m_task_id, true, nodelists[m_term].size());
    return 0;
}
