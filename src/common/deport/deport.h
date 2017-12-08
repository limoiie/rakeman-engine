//
// Created by limo on 2017/11/28.
//

#ifndef RAKEMAN_ENGINE_DEPORT_H
#define RAKEMAN_ENGINE_DEPORT_H

#include <vector>

#include "data/postingsmap.h"

class IDeport {
public:
    enum State {
        DISCONNECTED,
        UNCONNECTED,
        CONNECTING,
        CONNECTED
    };

    virtual bool fetchPostings(const std::vector<std::string> &terms, PostingsMap &map) = 0;
    virtual bool fetchPostings(const std::vector<std::string> &terms, std::vector<std::list<PostingNode>> &nodes) = 0;

    virtual bool storePostings(PostingsMap &map) = 0;
    virtual bool storePostings(const std::vector<std::string> &terms, std::vector<std::list<PostingNode>> &nodes) = 0;

    virtual bool deleteKey(const std::vector<std::string> &keys) = 0;

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual State connectState() = 0;

};

#endif //RAKEMAN_ENGINE_DEPORT_H
