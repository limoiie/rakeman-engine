//
// Created by limo on 2017/11/24.
//

#include "tokenizerimpl.h"

#include "../data/doc.h"
#include "../data/term.h"

int CTokenizerImpl::tokenize(const std::string &ik_str, std::vector<std::string> &o_tokens) {
    m_jieba->CutForSearch(ik_str, o_tokens);
    return 0;
}
