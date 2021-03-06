//
// Created by limo on 12/11/17.
//

#include "queryexpresstask.h"

#include <data/taskqueue.h>
#include <common/serializer.h>
#include <saker/queryexpresser/queryexpresser.h>
#include <common/log.h>


CQueryExpressTask::CQueryExpressTask(task_id_t task_id, std::string query)
        : ITask(task_id, QUERY_EXPRESS), m_query(std::move(query)) {
    // empty
}

std::shared_ptr<ITask> CQueryExpressTask::Deserialize(const std::string &str) {
    size_t offset = 0;
    task_id_t task_id;
    std::string query;

    // step 1: fetch the count of docs
    deserialize(str, offset, task_id);
    // step 2: fetch query
    deserialize(str, offset, query);

    limo::log_query_task(task_id, query);
    return std::make_shared<CQueryExpressTask>(task_id, query);
}

int CQueryExpressTask::work(std::shared_ptr<ITaskQueue> &queue) {
    saker::CQueryExpresser expresser;
    auto ids = expresser.express(m_query);

    // step 1: serialize the result
    std::string response;
    size_t offset = response.size();
    serialize(ids, response, offset);

    // step 2: response
    queue->pushResponse(m_task_id, QUERY_EXPRESS, true, response);

    limo::log_query_response(m_task_id, true, ids.size());
    return 0;
}
