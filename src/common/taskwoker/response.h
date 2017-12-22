//
// Created by limo on 12/13/17.
//

#ifndef RAKEMAN_ENGINE_RESPONSE_H
#define RAKEMAN_ENGINE_RESPONSE_H

#include <cppredis/includes/cpp_redis/core/client.hpp>
#include "task.h"

/**
 * Construct response by %task_type and send it to target
 * database through %client
 *
 * @param client Redis client
 * @param task_id Task id
 * @param task_type Task type
 * @param success Task process status
 * @param response Serialized response
 */
void Response(cpp_redis::client &client,
              task_id_t task_id,
              TaskType task_type,
              bool success,
              const std::string &response);

#endif //RAKEMAN_ENGINE_RESPONSE_H
