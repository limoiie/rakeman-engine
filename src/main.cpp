//
// Created by limo on 12/13/17.
//

#include <common/taskwoker/worker.h>
#include <common/factory/factoryfactory.h>
#include <data/redistaskqueue.h>

using namespace std;

int main() {
    CFactoryFactory::initialize();

    string host = "127.0.0.1";
    size_t port = 6379;
    shared_ptr<ITaskQueue> task_queue
            = make_shared<CRedisTaskQueue>(host, port);

    CWoker worker(task_queue);
    worker();

    return 0;
}