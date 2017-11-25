//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_TOKEN_H
#define RAKEMAN_ENGINE_TOKEN_H

#include <string>
#include <utility>

enum TermLocation {
    LOC_TITLE,
    LOC_CONTENT,
    LOC_COMMENT
};

/*
 * @brief Term which is split and normalized by tokenizer from doc
 */
struct Term {
    // id of the doc which contains this term
    long long int doc_id;
    // term string
    std::string term;
    // the character or property of this term. i.e. n, v, nz...
    std::string prop;
    // location of term in doc
    TermLocation location;
    // offset of this term in doc
    int offset;

    explicit Term(long long int i_doc_id,
                  std::string i_term = "",
                  std::string i_prop = "n",
                  TermLocation i_loc = LOC_CONTENT,
                  int i_offset = -1) :
            doc_id(i_doc_id),
            term(std::move(i_term)),
            prop(std::move(i_prop)),
            location(i_loc),
            offset(i_offset) {}
};

#endif //RAKEMAN_ENGINE_TOKEN_H
