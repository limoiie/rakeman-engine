#include <iostream>

#include "common/deport/redisdeport.h"

using namespace std;

int main() {
    //! Enable logging
    CRedisDeport deport("127.0.0.1", 6379);
    if (deport.connect()) {
        PostingsMap map;
        map["term1"] = {{123, 888}, {323, 999}, {7123, 777}};
        map["term2"] = {{324, 666}, {325, 555}, {7233, 111}};
        map["term3"] = {{589, 333}, {673, 222}, {7453, 444}};
//        deport.storePostingsInDict(map);

        std::vector<std::string> terms{"term2", "term1", "term3"};
        PostingsMap fak;
        deport.fetchPostings(terms, fak);

        for (auto &term : terms) {
            cout << "map: " << endl;
            for (auto node : map[term])
                cout << node.doc_id << ";" << node.term_freq << " ";
            cout << endl;
            cout << "node: " << endl;
            for (auto node : fak[term])
                cout << node.doc_id << ";" << node.term_freq << " ";
            cout << endl;
        }
    } else {
        throw runtime_error("failed to connect");
    }
    return 0;
}
