//
// Created by limo on 12/9/17.
//

#include <stdexcept>
#include <spdlog/spdlog.h>
#include <common/config.h>
#include "task.h"
#include "breakdocblocktask.h"
#include "sortandmergetempintodicttask.h"
#include "queryexpresstask.h"

std::shared_ptr<ITask> ITask::Deserialize(const std::string &str) {
    std::string serialized_task = str.substr(1, str.size()-1);
    switch (str[0]) {
        case BREAK_DOCUMENT_BLOCK:
            return CBreakDocBlockTask::Deserialize(serialized_task);
        case SORT_MERGE_POSTINGS:
            return CSortAndMergeTempIntoDictTask::Deserialize(serialized_task);
        case QUERY_EXPRESS:
            return CQueryExpressTask::Deserialize(serialized_task);
        default:
            throw std::runtime_error("Error: No such task type!");
    }
}
