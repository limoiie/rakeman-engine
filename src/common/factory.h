//
// Created by limo on 2017/11/28.
//

#ifndef RAKEMAN_ENGINE_FACTORY_H
#define RAKEMAN_ENGINE_FACTORY_H

#include <vector>

#include <data/postingsmap.h>

class IFactory {
public:
    virtual PostingsMap fetchPostings(std::vector<std::string> terms) = 0;
    virtual bool storePostings(PostingsMap map) = 0;
};

#endif //RAKEMAN_ENGINE_FACTORY_H
