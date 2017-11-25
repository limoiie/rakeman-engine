//
// Created by limo on 17-11-24.
//

#ifndef RAKEMAN_ENGINE_NORMALIZERIMPL_H
#define RAKEMAN_ENGINE_NORMALIZERIMPL_H

#include "normalizer.h"

class CNormalizerImpl : public INormalizer {
public:
    int normalize(std::vector<Term>& io_terms) override;
    ~CNormalizerImpl() override = default;
};


#endif //RAKEMAN_ENGINE_NORMALIZERIMPL_H
