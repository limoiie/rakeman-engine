//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_BSFETCHPOSTINGS_H
#define RAKEMAN_ENGINE_BSFETCHPOSTINGS_H

#include "statement.h"

namespace saker {

    class BSFetchPostings : public IStatement {
    public:
        explicit BSFetchPostings(const std::string &term);
        ~BSFetchPostings() override = default;

        result_type express() override;

    private:
        std::string m_term;

    };

}

#endif //RAKEMAN_ENGINE_BSFETCHPOSTINGS_H
