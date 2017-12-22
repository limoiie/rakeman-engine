//
// Created by limo on 12/13/17.
//

#include <common/config.h>
#include <common/serializer.h>
#include <common/integer2string.h>
#include "response.h"

static void response_break(cpp_redis::client &client,
                           task_id_t task_id,
                           bool success,
                           const std::string &response) {
    std::future<cpp_redis::reply> fut;
    if (success) {
        fut = client.decr(KEY_RESPONSE_NUM_BREAK_IN_PROCESSING);
    } else {
        std::string serialized_response;
        size_t offset = 0;
        serialize(task_id, serialized_response, offset);
        serialize(response, serialized_response, offset);
        fut = client.rpush(KEY_RESPONSE_BREAK_FAIL_QUEUE, {serialized_response});
    }
    client.commit();

    if (fut.get().is_error()) {
        // TODO: here should be a log
        std::cout << "Failed to pop out of task queue! Continue to pop" << std::endl;
    }
}

static void response_merge(cpp_redis::client &client,
                           task_id_t task_id,
                           bool success,
                           const std::string &response) {
    std::future<cpp_redis::reply> fut;
    if (success) {
        fut = client.decr(KEY_RESPONSE_NUM_MERGE_IN_PROCESSING);
    } else {
        std::string serialized_response;
        size_t offset = 0;
        serialize(task_id, serialized_response, offset);
        serialize(response, serialized_response, offset);
        fut = client.rpush(KEY_RESPONSE_MERGE_FAIL_QUEUE, {serialized_response});
    }
    client.commit();

    if (fut.get().is_error()) {
        // TODO: here should be a log
        std::cout << "Failed to pop out of task queue! Continue to pop" << std::endl;
    }
}

static void response_query(cpp_redis::client &client,
                           task_id_t task_id,
                           bool success,
                           const std::string &response) {
    std::string serialized_response;
    serialized_response = success ? "0" : "1";
    serialized_response.append(response);

    auto str_task_id = Integer2String(task_id);
    auto fut = client.hmset(KEY_RESPONSE_QUERY_HASH, {{str_task_id, serialized_response}});
    client.commit();

    if (fut.get().is_error()) {
        // TODO: here should be a log
        std::cout << "Failed to pop out of task queue! Continue to pop" << std::endl;
    }
}

void Response(cpp_redis::client &client,
              task_id_t task_id,
              TaskType task_type,
              bool success,
              const std::string &response) {

    switch (task_type) {
        case BREAK_DOCUMENT_BLOCK:
            response_break(client, task_id, success, response);
            break;
        case SORT_MERGE_POSTINGS:
            response_merge(client, task_id, success, response);
            break;
        case QUERY_EXPRESS:
            response_query(client, task_id, success, response);
            break;
        default:
            throw std::runtime_error("No such response type!");
    }
}