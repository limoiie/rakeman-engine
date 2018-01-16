//
// Created by limo on 12/4/17.
//

#ifndef RAKEMAN_ENGINE_TERMPROCESS_H
#define RAKEMAN_ENGINE_TERMPROCESS_H

#include <vector>
#include <string>
#include <map>

class Term;

void filterOutX(std::vector<Term> &i_term);

void countNER(std::vector<Term> &i_terms, std::map<std::string, int> o_counts);

#endif //RAKEMAN_ENGINE_TERMPROCESS_H
