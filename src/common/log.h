//
// Created by limo on 12/20/17.
//

#ifndef RAKEMAN_ENGINE_LOG_H
#define RAKEMAN_ENGINE_LOG_H

#include <string>
#include <common/taskwoker/task.h>

namespace limo {
    void log(const std::string &msg);

    void log_query_task(task_id_t task_id, const std::string &sentence);
    void log_break_task(task_id_t task_id, size_t num_docs);
    void log_merge_task(task_id_t task_id, const std::string &sentence);

    void log_query_response(task_id_t task_id, bool success, size_t num_ids);
    void log_break_response(task_id_t task_id, bool success, size_t num_docs);
    void log_merge_response(task_id_t task_id, bool success, size_t num_postings);

}



#endif //RAKEMAN_ENGINE_LOG_H
