//
// Created by limo on 12/13/17.
//

#include <common/taskwoker/worker.h>
#include <common/factory/factoryfactory.h>
#include <data/redistaskqueue.h>
#include <common/config.h>

using namespace std;

int main() {
    CFactoryFactory::initialize();

    string host = REDIS_ADDRESS;
    size_t port = REDIS_PORT;
    shared_ptr<ITaskQueue> task_queue
            = make_shared<CRedisTaskQueue>(host, port);

    CWoker worker(task_queue);
    worker();

    return 0;
}