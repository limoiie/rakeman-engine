//
// Created by limo on 2017/11/28.
//

#ifndef RAKEMAN_ENGINE_FACTORY_H
#define RAKEMAN_ENGINE_FACTORY_H

#include <vector>

#include "../data/postingsmap.h"

class IDeport {
public:
    enum State {
        DISCONNECTED,
        UNCONNECTED,
        CONNECTING,
        CONNECTED
    };

    virtual bool fetchPostings(std::vector<std::string> &terms, PostingsMap &map) = 0;
    virtual bool storePostings(PostingsMap &map) = 0;

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual State connectState() = 0;

};

#endif //RAKEMAN_ENGINE_FACTORY_H
