//
// Created by limo on 12/2/17.
//

#include <memory>

#include <common/factory/factoryfactory.h>
#include "bsfetchpostings.h"

saker::BSFetchPostings::BSFetchPostings(const std::string &term)
        : IStatement(FETCH),
          m_term(term) {}

saker::result_type saker::BSFetchPostings::express() {
    auto deport = CFactoryFactory::getInstance()
            ->getDeportFactory()
            ->get(CFactory<IDeport>::DEFAULT);
    PostingsMap map;
    deport->fetchPostings(std::vector<std::string>{m_term}, map);
    return map.begin()->second;
}
