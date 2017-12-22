//
// Created by limo on 12/20/17.
//

#include <spdlog/spdlog.h>
#include <common/taskwoker/task.h>
#include "config.h"

namespace limo {
    // TODO: consider removing to factory
    static auto console = spdlog::stdout_color_mt(NAME_LOG);

    void log(const std::string &msg) {
        console->info(msg);
    }

    void log_query_task(task_id_t task_id, const std::string &sentence) {
        console->info("Get QueryTask {0:08d}: {1}", task_id, sentence);
    }

    void log_break_task(task_id_t task_id, size_t num_docs) {
        console->info("Get BreakTask {0:08d}: {1:03d} docs", task_id, num_docs);
    }

    void log_merge_task(task_id_t task_id, const std::string &sentence) {
        console->info("Get BreakTask {0:08d}: {1}", task_id, sentence);
    }

    void log_query_response(task_id_t task_id, bool success, size_t num_ids) {
        if (success)
            console->info("Response QueryTask {0:08d}: Hit {1:04d} docs", task_id, num_ids);
        else
            console->error("Response QueryTask {0:08d}: Failed", task_id);
    }

    void log_break_response(task_id_t task_id, bool success, size_t num_docs) {
        if (success)
            console->info("Response BreakTask {0:08d}: Finish {1:03d} docs", task_id, num_docs);
        else
            console->error("Response BreakTask {0:08d}: Failed", task_id);
    }

    void log_merge_response(task_id_t task_id, bool success, size_t num_postings) {
        if (success)
            console->info("Response MergeTask {0:08d}: Success {1:04d} docs", task_id, num_postings);
        else
            console->error("Response MergeTask {0:08}: Failed", task_id);
    }

}