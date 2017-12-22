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

    tokenizer->tokenize(i_doc.title, o_terms);
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
}

// not in used since now we store the temp postings in the sorted set in redis
void SortPostingList(std::list<PostingNode> &io_terms) {
    // step 1: copy nodes from list into vector for doing quicker sort
    std::vector<PostingNode> nodes;
    for (auto &node : io_terms)
        nodes.push_back(std::move(node));
    io_terms.clear();

    // step 2: sort nodes and store the sorted nodes into nodelist
    std::sort(nodes.begin(), nodes.end());
    for (auto &node : nodes) {
        io_terms.push_back(std::move(node));
    }
}
