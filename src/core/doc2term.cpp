//
// Created by limo on 17-11-24.
//

#include "doc2term.h"

int CDoc2Term::doc2term(const Doc &ik_doc, std::vector<Term> &o_terms) const {
    int ret_code = m_tokenizer->tokenize(ik_doc, o_terms);
    if (ret_code == 0)
        ret_code = m_normalizer->normalize(o_terms);
    return ret_code;
}
