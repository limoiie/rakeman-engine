//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_DOCTOKENIZERIMPL_H
#define RAKEMAN_ENGINE_DOCTOKENIZERIMPL_H


#include "doctokenizer.h"

/*
 * @brief This class will tokenize the document to tokens, and this is just a
 * temp implement by wrapping jieba. Consider to replace it with a custom
 * tokenizer if there is enough time.
 */
class CDocTokenizerImpl : public IDocTokenizer {
public:
    int tokenize(CDoc doc, std::vector<CToken> &tokens) override;

};


#endif //RAKEMAN_ENGINE_DOCTOKENIZERIMPL_H
