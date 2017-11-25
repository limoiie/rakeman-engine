//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_DOCTOKENIZER_H
#define RAKEMAN_ENGINE_DOCTOKENIZER_H

#include <vector>

class Doc;
class Term;

class ITokenizer {
public:
    /*
     * @brief Tokenize input %code ik_doc and normalize and store the tokens
     * into %code o_tokens and we should make sure this function is thread-
     * safe since we are going to use this in a multi-thread env.
     *
     * return Process state code, 0 for success.
     */
    virtual int tokenize(const Doc& ik_doc, std::vector<Term> &o_terms) = 0;
    virtual ~ITokenizer() = default;;
};


#endif //RAKEMAN_ENGINE_DOCTOKENIZER_H