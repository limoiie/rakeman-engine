//
// Created by limo on 2017/11/24.
//

#include "tokenizerimpl.h"

#include "../data/doc.h"
#include "../data/term.h"

int CTokenizerImpl::tokenize(const Doc &ik_doc, std::vector<Term> &o_tokens) {
    std::vector<std::string> tokens;
    m_jieba->CutForSearch(ik_doc.content, tokens);
    for (const auto& token : tokens)
        o_tokens.emplace_back(ik_doc.id, token);
    return 0;
}
