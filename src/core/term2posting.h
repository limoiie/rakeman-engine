//
// Created by limo on 17-11-26.
//

#ifndef RAKEMAN_ENGINE_TERM2POSTING_H
#define RAKEMAN_ENGINE_TERM2POSTING_H

#include <memory>
#include <vector>

#include "../data/postingsmap.h"

class Term;

/*
 * @brief Posting terms to posting lists which are used on purpose of decreasing
 * space used by storing term-doc pairs.
 */
class CTerm2Posting {
public:
    int term2posting(std::vector<Term> &i_terms,
                     PostingsMap<>& o_postings) const;

};

#endif //RAKEMAN_ENGINE_TERM2POSTING_H
