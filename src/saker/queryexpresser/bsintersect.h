//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_BSINTERSECT_H
#define RAKEMAN_ENGINE_BSINTERSECT_H

#include "binarystatement.h"

namespace saker {

    class BSIntersect : public IBiStatement {
    public:
        explicit BSIntersect(std::shared_ptr<IStatement> stm1,
                             std::shared_ptr<IStatement> stm2);

        result_type express() override;
    };

}

#endif //RAKEMAN_ENGINE_BSINTERSECT_H
