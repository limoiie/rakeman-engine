//
// Created by limo on 11/28/17.
//

#ifndef RAKEMAN_ENGINE_QUERYPROCESS_H
#define RAKEMAN_ENGINE_QUERYPROCESS_H

#include <string>
#include <list>
#include <data/postingsmap.h>
#include <saker/queryexpresser/statement.h>

namespace saker {

    class CQueryExpresser {
    public:
        result_type express(const std::string &query);

    private:
        void lexical();
        void parser();

    };

}

#endif //RAKEMAN_ENGINE_QUERYPROCESS_H
