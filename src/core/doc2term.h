//
// Created by limo on 17-11-24.
//

#ifndef RAKEMAN_ENGINE_DOC2TERM_H
#define RAKEMAN_ENGINE_DOC2TERM_H

#include <memory>
#include <utility>

#include "tokenizer.h"
#include "normalizer.h"

class CDoc2Term {
public:
    CDoc2Term(std::shared_ptr<ITokenizer> tokenizer,
              std::shared_ptr<INormalizer> normalizer)
            : m_tokenizer(std::move(tokenizer)),
              m_normalizer(std::move(normalizer)) {}

    int doc2term(const Doc& ik_doc, std::vector<Term> &o_terms);

private:
    std::shared_ptr<ITokenizer> m_tokenizer;
    std::shared_ptr<INormalizer> m_normalizer;

};

#endif //RAKEMAN_ENGINE_DOC2TERM_H
