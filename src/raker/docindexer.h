//
// Created by limo on 12/7/17.
//

#ifndef RAKEMAN_ENGINE_DOCINDEXER_H
#define RAKEMAN_ENGINE_DOCINDEXER_H

#include <vector>
#include <string>

class Doc;

void ProcessDocs(const std::vector<Doc> &docs);

void SortPostingListByTerm(const std::string &term);

#endif //RAKEMAN_ENGINE_DOCINDEXER_H
