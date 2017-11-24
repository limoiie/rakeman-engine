//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_DOCTOKENIZER_H
#define RAKEMAN_ENGINE_DOCTOKENIZER_H

#include <vector>

class Doc;
class Term;

class IDocTokenizer {
public:
    virtual int tokenize(const Doc& ik_doc, std::vector<Term> &o_terms) = 0;

};


#endif //RAKEMAN_ENGINE_DOCTOKENIZER_H
