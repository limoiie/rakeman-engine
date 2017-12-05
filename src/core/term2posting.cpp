//
// Created by limo on 17-11-26.
//

#include "term2posting.h"

#include <algorithm>

#include "../data/term.h"

int term2posting(std::map<long long int, std::vector<Term>> &i_terms, PostingsMap &o_postings) {
    if (i_terms.empty()) return 0;
    // process document bu document
    for (auto &doc_id_terms : i_terms) {
        auto doc_id = doc_id_terms.first;
        auto &terms_by_doc = doc_id_terms.second;

        if (!terms_by_doc.empty()) {
            // sort the terms in one document
            std::sort(terms_by_doc.begin(), terms_by_doc.end());

            std::list<int> offsets;
            auto cur_term = terms_by_doc.front().term;
            for (auto &term : terms_by_doc) {
                if (cur_term == term.term) {  // store offsets of same terms into a list
                    offsets.push_back(term.offset);
                } else {  // all the same terms has been scanned
                    o_postings[cur_term].emplace_back(doc_id, offsets.size(), offsets);
                    cur_term = term.term;
                    offsets.clear();
                }
            }
            // the last term in the last doc has not been stored
            o_postings[cur_term].emplace_back(doc_id, offsets.size(), offsets);
        }
    }
    return 0;
}
