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

    double wf_idf;

    PostingNode(long long int i_doc_id = -1, // NOLINT
                int i_tf = 0,
                std::list<int> i_offsets = {},
                double i_wf_idf = 0)
            : doc_id(i_doc_id),
              term_offsets(std::move(i_offsets)),
              wf_idf(i_wf_idf) {}

    PostingNode(const PostingNode &c) {
        doc_id = c.doc_id;
        term_freq = c.term_freq;
//  TODO      term_offsets = c.term_offsets;
        wf_idf = c.wf_idf;
    }

    PostingNode(PostingNode &&c) noexcept {
        doc_id = c.doc_id;
        term_freq = c.term_freq;
//  TODO      term_offsets = std::move(c.term_offsets);
        wf_idf = c.wf_idf;
    }

    PostingNode& operator=(const PostingNode& c) {
        doc_id = c.doc_id;
        term_freq = c.term_freq;
//  TODO      term_offsets = c.term_offsets;
        wf_idf = c.wf_idf;
        return *this;
    }

    PostingNode& operator=(PostingNode&& c) noexcept {
        doc_id = c.doc_id;
        term_freq = c.term_freq;
//  TODO      term_offsets = std::move(c.term_offsets);
        wf_idf = c.wf_idf;
        return *this;
    }

    bool operator==(const PostingNode &rhs) const {
        return doc_id == rhs.doc_id;
    }

    bool operator!=(const PostingNode &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const PostingNode &rhs) const {
        return doc_id < rhs.doc_id;
    }

    bool operator>(const PostingNode &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const PostingNode &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const PostingNode &rhs) const {
        return !(*this < rhs);
    }

};

/**
 * @brief Postings map, the key of which is term, the value of which is the
 * list of docs who contain that term
 */
// todo: replace this %CWrappedStlMap with a trie-map
typedef CWrappedStlMap<std::string, std::list<PostingNode>> PostingsMap;

#endif //RAKEMAN_ENGINE_POSTINGLIST_H
