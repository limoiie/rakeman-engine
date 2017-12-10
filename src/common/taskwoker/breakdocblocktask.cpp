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

    // step 1: fetch the count of docs
    deserialize(str, offset, num_docs);

    // step 2: deserialize doc one by one
    std::vector<Doc> docs(num_docs);
    for (size_t i = 0; i < num_docs; ++i) {
        deserialize(str, offset, docs[i]);
    }
    return std::make_shared<CBreakDocBlockTask>(std::move(docs));
}

int CBreakDocBlockTask::work(ITaskQueue &queue) {
    auto deport = CFactoryFactory::getInstance()
            ->getDeportFactory()
            ->get(CFactory<IDeport>::DEFAULT);

    // step 1: break doc into terms one by one
    doc_id_map_terms_t doc_id_map_terms;
    for (const auto &doc : m_docs) {
        doc_id_map_terms[doc.id] = {};
    }
    for (const auto &doc : m_docs) {
        Doc2Terms(doc, doc_id_map_terms[doc.id]);
        filterOutX(doc_id_map_terms[doc.id]);
    }

    // step 2: merge terms into posting lists (leave the postings list unsorted
    // since there are many other threads are doing doc2terms at the same time
    // and a good idea is we sort the posting list for each term after all docs
    // have been termed.)
    PostingsMap postingsMap;
    Terms2PostingList(doc_id_map_terms, postingsMap);

    // step 3: append the posting lists into the deport.
    deport->appendPostingsToTemp(postingsMap);
    return 0;
}
