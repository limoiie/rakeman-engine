//
// Created by limo on 12/2/17.
//

#include "bsconjunction.h"

#include <saker/postingsop.hpp>

saker::BSConjunction::BSConjunction(std::shared_ptr<saker::IStatement> cmd1,
                                    std::shared_ptr<saker::IStatement> cmd2)
        : IBiStatement(OR, std::move(cmd1), std::move(cmd2)) {}

saker::result_type saker::BSConjunction::express(){
    auto param1 = m_statement1->express();
    auto param2 = m_statement2->express();
    result_type res;
    ConjunctLists(param1, param2, res);
    return res;
}
