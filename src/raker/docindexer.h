//
// Created by limo on 12/7/17.
//

#ifndef RAKEMAN_ENGINE_DOCINDEXER_H
#define RAKEMAN_ENGINE_DOCINDEXER_H

#include <vector>
#include <list>
#include <string>
#include <data/postingsmap.h>
#include <data/doc.h>

class Doc;
class Term;

typedef std::map<doc_id_t, std::vector<Term>> doc_id_map_terms_t;

void Doc2Terms(const Doc &i_doc, std::vector<Term> &o_terms);

void Terms2PostingList(const doc_id_map_terms_t &i_terms, PostingsMap &o_postings);

void SortPostingList(std::list<PostingNode> &io_terms);

#endif //RAKEMAN_ENGINE_DOCINDEXER_H
