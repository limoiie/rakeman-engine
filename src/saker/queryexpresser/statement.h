//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_COMMAND_H
#define RAKEMAN_ENGINE_COMMAND_H

#include <list>
#include <data/postingsmap.h>

namespace saker {

    typedef std::list<PostingNode> param_type;
    typedef std::list<PostingNode> result_type;

    enum StatOp {
        TRIVIAL,
        AND,
        OR,
        NOT
    };

    class IStatement {
    public:
        explicit IStatement(StatOp op) : op(op) {}
        virtual result_type express() = 0;

        const StatOp op;

    };

}

#endif //RAKEMAN_ENGINE_COMMAND_H
