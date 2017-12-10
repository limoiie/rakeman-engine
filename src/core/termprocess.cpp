//
// Created by limo on 12/4/17.
//

#include "termprocess.h"
#include "data/term.h"

void filterOutX(std::vector<Term> &io_term) {
    std::vector<Term> temp;
    std::swap(temp, io_term);

    for (auto &term : temp) {
        if (term.prop != "x" && term.prop != "uj") {
            io_term.push_back(std::move(term));
        }
    }
}
