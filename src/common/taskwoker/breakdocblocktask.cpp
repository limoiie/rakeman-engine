//
// Created by limo on 12/8/17.
//

#include "breakdocblocktask.h"

#include <data/doc.h>
#include <data/term.h>
#include <common/serializer.h>
#include <raker/docindexer.h>
#include <common/factory/factoryfactory.h>
#include <core/termprocess.h>
#include <data/taskqueue.h>
#include <common/log.h>

CBreakDocBlockTask::CBreakDocBlockTask(task_id_t task_id, std::vector<Doc> docs)
        : ITask(task_id, BREAK_DOCUMENT_BLOCK),
          m_docs(std::move(docs)) {
    // empty
}

/**
 * @param str num|doc_str|doc_str|...
 */
std::shared_ptr<ITask> CBreakDocBlockTask::Deserialize(const std::string &str) {
    size_t offset = 0;
    size_t num_docs = 0;
    task_id_t task_id;

    // step 1: fetch the count of docs
    deserialize(str, offset, task_id);
    deserialize(str, offset, num_docs);

    // step 2: deserialize doc one by one
    std::vector<Doc> docs(num_docs);
    for (size_t i = 0; i < num_docs; ++i) {
        deserialize(str, offset, docs[i]);
    }

    limo::log_break_task(task_id, num_docs);
    return std::make_shared<CBreakDocBlockTask>(task_id, std::move(docs));
}

int CBreakDocBlockTask::work(std::shared_ptr<ITaskQueue> &queue) {
    auto deport = CFactoryFactory::getInstance()
            ->getDeportFactory()
            ->get(CFactory<IDeport>::DEFAULT);

    // step 1: break doc into terms one by one
    doc_id_map_terms_t doc_id_map_terms;
    for (const auto &doc : m_docs) {
        doc_id_map_terms[doc.id] = {};
    }

    std::map<std::string, int> counts;
    for (const auto &doc : m_docs) {
        Doc2Terms(doc, doc_id_map_terms[doc.id]);
        filterOutX(doc_id_map_terms[doc.id]);
        countNER(doc_id_map_terms[doc.id], counts);
    }

    // step 2: merge terms into posting lists (leave the postings list unsorted
    // since there are many other threads are doing doc2terms at the same time
    // and a good idea is we sort the posting list for each term after all docs
    // have been termed.)
    PostingsMap postingsMap;
    Terms2PostingList(doc_id_map_terms, postingsMap);

    // step 3: append the posting lists into the deport.
    deport->appendPostingsToTemp(postingsMap);

    // step 4: response, and 1 for success
    queue->pushResponse(m_task_id, BREAK_DOCUMENT_BLOCK, true, "");

    limo::log_break_response(m_task_id, true, m_docs.size());

    return 0;
}
