//
// Created by limo on 17-11-24.
//

#include "doc2term.h"
#include "../data/doc.h"

int CDoc2Term::doc2term(const Doc &ik_doc, std::vector<Term> &o_terms) const {
    std::vector<std::string> strs;
    int ret_code = m_tokenizer->tokenize(ik_doc.content, strs);
    for (const auto& str : strs)
        o_terms.emplace_back(ik_doc.id, str);
    if (ret_code == 0)
        ret_code = m_normalizer->normalize(o_terms);
    return ret_code;
}
