//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_DOCTOKENIZER_H
#define RAKEMAN_ENGINE_DOCTOKENIZER_H

#include <vector>

#include "../common/data/doc.h"
#include "../common/data/token.h"

class IDocTokenizer {
public:
    virtual int tokenize(CDoc doc, std::vector<CToken> &tokens) = 0;

};


#endif //RAKEMAN_ENGINE_DOCTOKENIZER_H
