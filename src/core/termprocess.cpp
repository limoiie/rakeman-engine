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
        } else if (term.prop == "x" && term.term.size() > 5) {
            io_term.push_back(std::move(term));
        }
    }
}

void countNER(std::vector<Term> &i_terms, std::map<std::string, int> o_counts) {
    for (const auto& term : i_terms) {
        if (term.prop.size() == 2 && term.prop[0] == 'n') {
            switch (term.prop[1]) {
                case 't': case 'z': case 'r': case 's':
                    o_counts[term.term] += term.offset;
                    break;
                default:
                    break;
            }
        }
    }
}
