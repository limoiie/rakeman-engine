//
// Created by limo on 12/2/17.
//

#include "bsintersect.h"

#include <saker/postingsop.hpp>

saker::BSIntersect::BSIntersect(std::shared_ptr<saker::IStatement> stm1,
                                std::shared_ptr<saker::IStatement> stm2)
        : IBiStatement(AND, std::move(stm1), std::move(stm2)) {}

saker::result_type saker::BSIntersect::express() {
    auto param1 = m_statement1->express();
    auto param2 = m_statement2->express();
    result_type res;
    IntersectLists(param1, param2, res);
    return res;
}
