//
// Created by limo on 17-11-28.
//

#ifndef RAKEMAN_ENGINE_POSTINGSOP_H
#define RAKEMAN_ENGINE_POSTINGSOP_H

#include <list>
#include <data/postingsmap.h>
#include <vector>
#include <set>
#include <common/deport/deport.h>
#include <data/doc.h>
#include <algorithm>

using namespace std;

void InitWfIdf(std::vector<std::list<PostingNode>> &nodelists, size_t num_docs);

void SortDocNodesByWfIdf(std::list<PostingNode> &nodes, std::vector<doc_id_t> & doc_ids);

void IntersectLists(const std::list<PostingNode> &i_lt1,
                    const std::list<PostingNode> &i_lt2,
                    std::list<PostingNode> &o_lt3);

void ConjunctLists(const std::list<PostingNode> &i_lt1,
                   const std::list<PostingNode> &i_lt2,
                   std::list<PostingNode> &o_lt3);

void ExcludeLists(const std::list<PostingNode> &i_src,
                  const std::list<PostingNode> &i_exc,
                  std::list<PostingNode> &o_tgt);

#endif //RAKEMAN_ENGINE_POSTINGSOP_H
