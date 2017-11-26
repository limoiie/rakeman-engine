//
// Created by limo on 17-11-26.
//

#include "term2posting.h"

#include <algorithm>

#include "../data/term.h"

int CTerm2Posting::term2posting(std::vector<Term> &i_terms,
                                PostingsMap<> &o_postings) const {
    if (i_terms.empty()) return 0;

    // sort terms by doc id in order to counting tf in one doc
    std::sort(i_terms.begin(), i_terms.end());

    int term_freq = 0;
    auto cur_doc_id = i_terms[0].doc_id;
    auto cur_term = i_terms[0].term;
    for (const auto& term : i_terms) {
        if (cur_doc_id == term.doc_id) {
            if (cur_term == term.term)
                ++term_freq;
            else {  // one term has finished
                o_postings[cur_term].emplace_back(cur_doc_id, term_freq);
                cur_term = term.term;
                term_freq = 1;
            }
        } else {  // one doc has finished
            o_postings[cur_term].emplace_back(cur_doc_id, term_freq);
            cur_doc_id = term.doc_id;
            cur_term = term.term;
            term_freq = 1;
        }
    }

    // the last term in the last doc has not been stored
    o_postings[cur_term].emplace_back(cur_doc_id, term_freq);

    return 0;
}
