//
// Created by limo on 12/9/17.
//

#include <stdexcept>
#include "task.h"
#include "breakdocblocktask.h"
#include "sortunsortedpostinglisttask.h"

std::shared_ptr<ITask> ITask::Deserialize(const std::string &str) {
    switch (str[0]) {
        case BREAK_DOCUMENT_BLOCK:
            return CBreakDocBlockTask::Deserialize(str.substr(1, str.size()-1));
        case SORT_UNSORTED_POSTING_LIST:
            return CSortUnsortedPostingListTask::Deserialize(str.substr(1, str.size()-1));
        default:
            throw std::runtime_error("Error: No such task type!");
    }
}
