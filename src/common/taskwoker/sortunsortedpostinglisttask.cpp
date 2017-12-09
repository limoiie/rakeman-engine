//
// Created by limo on 12/9/17.
//

#include <raker/docindexer.h>
#include "sortunsortedpostinglisttask.h"

CSortUnsortedPostingListTask::CSortUnsortedPostingListTask(const std::string &term)
        : ITask(SORT_UNSORTED_POSTING_LIST),
          m_term(term) {
    // empty
}

std::shared_ptr<ITask> CSortUnsortedPostingListTask::Deserialize(const std::string & str) {
    return std::make_shared<CSortUnsortedPostingListTask>(str);
}

int CSortUnsortedPostingListTask::work() {
    SortPostingListByTerm(m_term);
    return 0;
}
