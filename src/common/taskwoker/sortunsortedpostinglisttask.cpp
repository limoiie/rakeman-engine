//
// Created by limo on 12/9/17.
//

#include <raker/docindexer.h>
#include <common/deport/deport.h>
#include <common/factory/deportfactory.h>
#include <common/factory/factoryfactory.h>
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
    auto deport = CFactoryFactory::getInstance()
            ->getDeportFactory()
            ->get(CFactory<IDeport>::DEFAULT);

    // step 1: fetch posting list by term
    std::vector<std::list<PostingNode>> nodelists;
    deport->fetchPostings(std::vector<std::string>{m_term}, nodelists);

    // step 2: sort posting list
    SortPostingList(nodelists[0]);

    // step 3: store posting list by term
    deport->deleteKey(std::vector<std::string>{m_term});
    deport->storePostings(std::vector<std::string>{m_term}, nodelists);
    return 0;
}
