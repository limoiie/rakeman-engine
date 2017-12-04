//
// Created by limo on 2017/11/24.
//

#include "tokenizerimpl.h"

#include "../data/term.h"

int CTokenizerImpl::tokenize(const std::string &ik_str, std::vector<std::string> &o_tokens) {
    m_jieba->CutForSearch(ik_str, o_tokens);
    return 0;
}

int CTokenizerImpl::tokenize(const std::string &ik_str, std::vector<Term> &o_terms) {
    std::vector<cppjieba::Word> words;
    m_jieba->CutForSearch(ik_str, words);
    for (auto &word : words)
        o_terms.emplace_back(std::move(word.word),
                             m_jieba->LookupTag(word.word),
                             LOC_CONTENT,
                             word.offset);
    return 0;
}
