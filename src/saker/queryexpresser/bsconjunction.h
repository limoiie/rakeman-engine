//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_BCCONJUNCTION_H
#define RAKEMAN_ENGINE_BCCONJUNCTION_H

#include "binarystatement.h"

namespace saker {

    class BSConjunction : public IBiStatement {
    public:
        explicit BSConjunction(std::shared_ptr<IStatement> cmd1,
                               std::shared_ptr<IStatement> cmd2);

        result_type express() override;
    };

}

#endif //RAKEMAN_ENGINE_BCCONJUNCTION_H
