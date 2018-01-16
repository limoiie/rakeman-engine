//
// Created by limo on 12/7/17.
//

#include "docindexer.h"

#include <data/term.h>
#include <common/factory/factoryfactory.h>

void Doc2Terms(const Doc &i_doc, std::vector<Term> &o_terms) {
    auto tokenizer = CFactoryFactory::getInstance()
            ->getTokenizerFactory()
            ->get(CFactory<ITokenizer>::DEFAULT);

    size_t start_ind = o_terms.size();
    tokenizer->tokenize(i_doc.title, o_terms);
    for (size_t i = start_ind; i < o_terms.size(); ++i) {
        o_terms[i].location = LOC_TITLE;
    }
    tokenizer->tokenize(i_doc.content, o_terms);
}

void Terms2PostingList(const std::map<doc_id_t, std::vector<Term>> &i_terms,
                       PostingsMap &o_postings) {

    if (i_terms.empty()) return;
    // process document by document
    for (auto itr = i_terms.begin(); itr != i_terms.end(); ++itr) {
        auto doc_id = itr->first;
        auto terms_by_doc = itr->second;

        if (!terms_by_doc.empty()) {
            // sort the terms in one document
            std::sort(terms_by_doc.begin(), terms_by_doc.end());

            std::list<int> offsets;
            int term_freq = 0;
            auto cur_term = terms_by_doc.front().term;
            for (auto &term : terms_by_doc) {
                int special_n = 1;
                if (term.prop[0] == 'n' && term.prop.size() >= 2 &&
                        (term.prop[1] == 'r' || term.prop[2] == 't')) {
                    special_n = 4;
                }
                if (cur_term == term.term) {  // store offsets of same terms into a list
                    if (term.location == LOC_TITLE) // !!!!!!NOTE: TRICK IMPL
                        term_freq += 150 * special_n;
                    else if (term.location == LOC_CONTENT)
                        term_freq += 1 * special_n;
                } else {  // all the same terms has been scanned
                    o_postings[cur_term].emplace_back(doc_id, term_freq, offsets);
                    cur_term = term.term;
                    term_freq = 0;
                }
            }
            // the last term in the last doc has not been stored
            o_postings[cur_term].emplace_back(doc_id, term_freq, offsets);
        }
    }
}
