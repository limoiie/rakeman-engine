//
// Created by limo on 17-11-25.
//

#ifndef RAKEMAN_ENGINE_POSTINGLIST_H
#define RAKEMAN_ENGINE_POSTINGLIST_H

#include <memory>
#include <list>
#include <utility>
#include <map>

struct PostingNode {
    long long int doc_id;
    int term_freq;
    std::list<int> term_offsets;

    explicit PostingNode(long long int i_doc_id,
                         int i_tf = 0,
                         std::list<int> i_offsets = {})
            : doc_id(i_doc_id),
              term_freq(i_tf),
              term_offsets(std::move(i_offsets)) {}

};

struct PostingsMap {
    typedef PostingNode node_type;
    typedef std::list<node_type> list_type;

    // todo: consider replacing map with trie
    std::map<std::string, list_type> postings;
    std::string term;

    explicit PostingsMap(std::string i_term)
            : term(std::move(i_term)),
              postings() {}

};

#endif //RAKEMAN_ENGINE_POSTINGLIST_H
