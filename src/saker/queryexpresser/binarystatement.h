//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_BISTATEMENT_H
#define RAKEMAN_ENGINE_BISTATEMENT_H

#include "statement.h"

#include <utility>

namespace saker {

    class IBiStatement : public IStatement {
    public:
        explicit IBiStatement(StatOp op,
                                std::shared_ptr<IStatement> stm1,
                                std::shared_ptr<IStatement> stm2)
                : IStatement(op),
                  m_statement1(std::move(stm1)),
                  m_statement2(std::move(stm2)) {}

    protected:
        std::shared_ptr<IStatement> m_statement1{};
        std::shared_ptr<IStatement> m_statement2{};

    };

}

#endif //RAKEMAN_ENGINE_BISTATEMENT_H
