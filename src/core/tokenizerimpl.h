//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_DOCTOKENIZERIMPL_H
#define RAKEMAN_ENGINE_DOCTOKENIZERIMPL_H

#include <bits/shared_ptr.h>

#include <cppjieba/Jieba.hpp>

#include "tokenizer.h"

/*
 * @brief This class will tokenize the document to terms, and this is just a
 * temp implement by wrapping jieba. Consider to replace it with a custom
 * tokenizer if there is enough time.
 */
class CDocTokenizerImpl : public IDocTokenizer {
public:
    /*
     * @brief Construct the impl with input jieba engine. It's caller's
     * responsibility to make sure the jieba engine has been initialled
     * successfully.
     */
    explicit CDocTokenizerImpl(std::shared_ptr<cppjieba::Jieba> jieba)
            : m_jieba(jieba) {}

    /*
     * @brief Tokenize input %code ik_doc and store the terms into %code
     * o_terms
     *
     * return Process state code, 0 for success.
     */
    int tokenize(const Doc& ik_doc, std::vector<Term> &o_terms) override;

private:
    // the term engine used to tokenize doc to terms. this engine will not
    // change its context while it is tokenizing, which means it can be used
    // concurrently and that's also the reason why we use a ptr to point to
    // one public instance of jieba
    std::shared_ptr<cppjieba::Jieba> m_jieba;

};


#endif //RAKEMAN_ENGINE_DOCTOKENIZERIMPL_H
