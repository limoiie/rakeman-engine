//
// Created by limo on 12/23/17.
//

#include <list>
#include <functional>
#include <data/postingsmap.h>
#include <vector>
#include <set>
#include <cmath>
#include <data/doc.h>
#include <algorithm>
#include <iostream>

void InitWfIdf(std::vector<std::list<PostingNode>> &nodelists, size_t num_docs) {
    for (auto &nodelist : nodelists) {
        size_t df = nodelist.size();
        if ((df << 1) < num_docs) {
            double NDdf = static_cast<double>(num_docs-df) / df;
            double idf = 1 + log(NDdf);
            for (auto &node : nodelist) {
                double wf = 1 + log(node.term_freq+1);
                node.wf_idf = wf * idf;
            }
        } // else do nothing
    }
}

void SortDocNodesByWfIdf(std::list<PostingNode> &nodes, std::vector<doc_id_t> & doc_ids) {
    std::vector<PostingNode> node_vec;
    node_vec.reserve(nodes.size());
    for (auto &node : nodes) {
        node_vec.emplace_back(node);
    }

    sort(node_vec.begin(), node_vec.end(), [](const PostingNode& lhv, const PostingNode& rhv)->bool{
        return lhv.wf_idf > rhv.wf_idf;
    });

    doc_ids.reserve(node_vec.size());
    for (auto &node : node_vec) {
        doc_ids.push_back(node.doc_id);
    }
}

void IntersectLists(const std::list<PostingNode> &i_lt1,
                    const std::list<PostingNode> &i_lt2,
                    std::list<PostingNode> &o_lt3) {
    auto itr1 = i_lt1.begin();
    auto itr2 = i_lt2.begin();
    while (itr1 != i_lt1.end() && itr2 != i_lt2.end()) {
        if (itr1->doc_id < itr2->doc_id) {
            ++itr1;
        } else if (itr1->doc_id > itr2->doc_id) {
            ++itr2;
        } else {
            o_lt3.push_back(PostingNode(itr1->doc_id, 0, {},
                                        itr1->wf_idf + itr2->wf_idf));
            ++itr1, ++itr2;
        }
    }
}

void ConjunctLists(const std::list<PostingNode> &i_lt1,
                   const std::list<PostingNode> &i_lt2,
                   std::list<PostingNode> &o_lt3) {
    auto itr1 = i_lt1.begin();
    auto itr2 = i_lt2.begin();
    while (itr1 != i_lt1.end() && itr2 != i_lt2.end()) {
        if (itr1->doc_id < itr2->doc_id) {
            o_lt3.push_back(PostingNode(itr1->doc_id, 0, {},
                                        itr1->wf_idf));
            ++itr1;
        } else if (itr1->doc_id > itr2->doc_id) {
            o_lt3.push_back(PostingNode(itr2->doc_id, 0, {},
                                        itr2->wf_idf));
            ++itr2;
        } else {
            o_lt3.push_back(PostingNode(itr1->doc_id, 0, {},
                                        itr1->wf_idf + itr2->wf_idf));
            ++itr1; ++itr2;
        }
    }
    if (itr1 != i_lt1.end())
        o_lt3.insert(o_lt3.end(), itr1, i_lt1.end());
    if (itr2 != i_lt2.end())
        o_lt3.insert(o_lt3.end(), itr2, i_lt2.end());
}

void ExcludeLists(const std::list<PostingNode> &i_src,
                  const std::list<PostingNode> &i_exc,
                  std::list<PostingNode> &o_tgt) {
    auto itr1 = i_src.begin();
    auto itr2 = i_exc.begin();
    while (itr1 != i_src.end() && itr2 != i_exc.end()) {
        if (itr1->doc_id < itr2->doc_id) {
            o_tgt.push_back(PostingNode(itr1->doc_id, 0, {},
                                        itr1->wf_idf));
            ++itr1;
        } else if (itr1->doc_id > itr2->doc_id) {
            ++itr2;
        } else {
            ++itr1; ++itr2;
        }
    }
    if (itr1 != i_src.end())
        o_tgt.insert(o_tgt.end(), itr1, i_src.end());
}
