//
// Created by limo on 12/2/17.
//

#include <string>
#include <iostream>
#include <saker/queryexpresser/statement.h>
#include <saker/queryexpresser/bsintersect.h>

#include "gtest/gtest.h"

namespace {
    using namespace std;
    using namespace saker;

    class BSTerminal : public IStatement {
    public:
        explicit BSTerminal(result_type &nodes)
                : IStatement(TRIVIAL), nodes(nodes) {}

        result_type express() override {
            return move(nodes);
        }

        saker::result_type &nodes;

    };

    TEST(QueryExpresserTests, IntersecTest) { // NOLINT
        list<PostingNode> nodes1 = {{123, 888}, {323, 999}, {713, 777}};
        list<PostingNode> nodes2 = {{322, 666}, {323, 999}, {7133, 111}};
        BSIntersect intersect(make_shared<BSTerminal>(nodes1),
                              make_shared<BSTerminal>(nodes2));
        auto res = intersect.express();
        ASSERT_EQ(int(res.size()), 1);
        ASSERT_EQ(res.front().doc_id, 323);
        ASSERT_EQ(res.front().term_freq, 999);
    }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
