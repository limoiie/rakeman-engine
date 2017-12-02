//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_BSEXCLUDE_H
#define RAKEMAN_ENGINE_BSEXCLUDE_H

#include "binarystatement.h"

namespace saker {

    class BSExclude : public IBiStatement {
    public:
        explicit BSExclude(std::shared_ptr<IStatement> stm1,
                           std::shared_ptr<IStatement> stm2);
        ~BSExclude() override = default;

        result_type express() override;
    };

}

#endif //RAKEMAN_ENGINE_BSEXCLUDE_H
