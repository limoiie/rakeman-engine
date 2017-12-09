//
// Created by limo on 12/8/17.
//

#include <common/serializer.h>

#include <utility>
#include <raker/docindexer.h>
#include "breakdocblocktask.h"

CBreakDocBlockTask::CBreakDocBlockTask(std::vector<Doc> docs)
        : ITask(BREAK_DOCUMENT_BLOCK),
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

int CBreakDocBlockTask::work() {
    ProcessDocs(m_docs);
    return 0;
}
