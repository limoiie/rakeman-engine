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

    virtual size_t countDocs() = 0;

    virtual bool fetchPostings(const std::vector<std::string> &terms, PostingsMap &map) = 0;
    virtual bool fetchPostings(const std::vector<std::string> &terms, std::vector<std::list<PostingNode>> &nodes) = 0;

    virtual bool storePostingsInDict(PostingsMap &map) = 0;
    virtual bool appendPostingsToTemp(PostingsMap &map) = 0;

    virtual bool addHotNERCounts(const std::map<std::string, int> &counts) = 0;

    virtual bool deleteTermsInDict(const std::vector<std::string> &keys) = 0;
    virtual bool deleteTermsInTemp(const std::vector<std::string> &keys) = 0;

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual State connectState() = 0;

};

#endif //RAKEMAN_ENGINE_DEPORT_H
