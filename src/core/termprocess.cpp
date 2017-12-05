//
// Created by limo on 12/4/17.
//

#include "termprocess.h"
#include "data/term.h"

void filterOutX(const std::vector<Term> &i_term, std::vector<Term> &o_term) {
    for (auto &term : i_term) {
        if (term.prop != "x" && term.prop != "uj") {
            o_term.push_back(term);
        }
    }
}
