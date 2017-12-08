//
// Created by limo on 12/7/17.
//

#include <data/term.h>
#include <data/doc.h>
#include <data/postingsmap.h>
#include <algorithm>
#include <common/factory/factoryfactory.h>
#include "docindexer.h"

typedef std::vector<std::pair<doc_id_t, std::vector<Term>>> doc_terms_pair_t;

/*
 * @brief Posting terms to posting lists which are used on purpose of decreasing
 * space used by storing term-doc pairs.
 */
static int term2posting(const doc_terms_pair_t &i_terms, PostingsMap& o_postings);

void processDocs(const std::vector<Doc> &docs) {
    auto tokenizer = CFactoryFactory::getInstance()
            ->getTokenizerFactory()
            ->get(CFactory<ITokenizer>::DEFAULT);

    doc_terms_pair_t doc_terms_pairs;
    std::vector<Term> terms;
    PostingsMap postingsMap;
    for (const auto &doc : docs) {
        tokenizer->tokenize(doc.content, terms);
        doc_terms_pairs.emplace_back(doc.id, std::move(terms));
        terms.clear();
    }
    term2posting(doc_terms_pairs, postingsMap);
}

void sortPostingListByTerm(const std::string &term) {
    auto deport = CFactoryFactory::getInstance()
            ->getDeportFactory()
            ->get(CFactory<IDeport>::DEFAULT);

    // step 1: fetch unsorted node by term
    std::vector<std::list<PostingNode>> nodelists;
    deport->fetchPostings(std::vector<std::string>{term}, nodelists);

    // step 2: copy nodes from list into vector for quick sort
    std::vector<PostingNode> nodes;
    for (auto &node : nodelists[0])
        nodes.push_back(std::move(node));

    // step 3: sort nodes and store the sorted nodes into nodelist
    std::sort(nodes.begin(), nodes.end());
    std::copy(nodes.begin(), nodes.end(), nodelists[0].begin());

    // step 4: store nodes into deport
    deport->storePostings(std::vector<std::string>{term}, nodelists);
}

int term2posting(const doc_terms_pair_t &i_terms, PostingsMap& o_postings) {
    if (i_terms.empty()) return 0;
    // process document bu document
    for (auto &doc_id_terms : i_terms) {
        auto doc_id = doc_id_terms.first;
        auto terms_by_doc = doc_id_terms.second;

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
