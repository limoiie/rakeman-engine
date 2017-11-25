//
// Created by limo on 17-11-24.
//

#ifndef RAKEMAN_ENGINE_NORMALIZER_H
#define RAKEMAN_ENGINE_NORMALIZER_H

#include <vector>

#include "../data/term.h"

class INormalizer {
public:
    /*
     * @brief Normalize tokens to normed terms by stemming, correct ...
     * and we should make sure that this function is thread-safe since
     * we are going to use this in a multi-thread env
     *
     * return Process state code, 0 for success
     */
    virtual int normalize(std::vector<Term>& io_terms) = 0;
    virtual ~INormalizer() = default;
};

#endif //RAKEMAN_ENGINE_NORMALIZER_H
