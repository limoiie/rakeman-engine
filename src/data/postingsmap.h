//
// Created by limo on 17-11-25.
//

#ifndef RAKEMAN_ENGINE_POSTINGLIST_H
#define RAKEMAN_ENGINE_POSTINGLIST_H

#include <memory>
#include <list>
#include <utility>
#include <map>
#include "map.h"
#include "wrappedstlmap.hpp"

/**
 * @brief Posting Node
 */
struct PostingNode {
    long long int doc_id;
    int term_freq;
    std::list<int> term_offsets{};

    explicit PostingNode(long long int i_doc_id,
                         int i_tf = 0,
                         std::list<int> i_offsets = {})
            : doc_id(i_doc_id),
              term_freq(i_tf),
              term_offsets(std::move(i_offsets)) {}

};

/**
 * @brief Postings map, the key of which is term, the value of which is the
 * list of docs who contain that term
 */
// todo: replace this %CWrappedStlMap with a trie-map
template <typename M = CWrappedStlMap<std::string, std::list<PostingNode>>>
struct PostingsMap {
    typedef PostingNode node_type;
    typedef std::string term_type;
    typedef std::list<node_type> posting_type;

    PostingsMap() : postings(std::make_shared<M>()) {}

    inline
    posting_type& operator[](const term_type& i_key) {
        return (*postings)[i_key];
    }

    inline
    posting_type& operator[](term_type&& i_key) {
        return (*postings)[std::move(i_key)];
    }

    // posting map
    std::shared_ptr<IMap<term_type, posting_type, typename M::iterator>> postings;

};

#endif //RAKEMAN_ENGINE_POSTINGLIST_H
