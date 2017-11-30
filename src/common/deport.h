//
// Created by limo on 2017/11/28.
//

#ifndef RAKEMAN_ENGINE_FACTORY_H
#define RAKEMAN_ENGINE_FACTORY_H

#include <vector>

#include "../data/postingsmap.h"

class IDeport {
public:
    virtual PostingsMap fetchPostings(std::vector<std::string> &terms) = 0;
    virtual bool storePostings(PostingsMap &map) = 0;

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual State connectState() = 0;

    enum State {
        DISCONNECTED,
        UNCONNECTED,
        CONNECTING,
        CONNECTED
    };

};

#endif //RAKEMAN_ENGINE_FACTORY_H
