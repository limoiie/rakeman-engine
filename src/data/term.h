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
    // term string
    std::string term;
    // the character or property of this term. i.e. n, v, nz...
    std::string prop;
    // location of term in doc
    TermLocation location;
    // offset of this term in doc
    int offset;
    // todo: consider add term_id field (update operator< after added)

    explicit Term(std::string i_term = "",
                  std::string i_prop = "x",
                  TermLocation i_loc = LOC_CONTENT,
                  int i_offset = -1) :
            term(std::move(i_term)),
            prop(std::move(i_prop)),
            location(i_loc),
            offset(i_offset) {}

    /**
     * @brief Defined for counting tf in a doc
     */
    bool operator<(const Term &rhs) const {
        int cmp = term.compare(rhs.term);
        if (cmp != 0) return cmp < 0;
        return offset < rhs.offset;
    }

    bool operator>(const Term &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Term &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Term &rhs) const {
        return !(*this < rhs);
    }
};

#endif //RAKEMAN_ENGINE_TOKEN_H
