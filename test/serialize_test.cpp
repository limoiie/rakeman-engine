//
// Created by limo on 12/1/17.
//

#include <string>
#include <iostream>
#include <data/postingsmap.h>

#include "gtest/gtest.h"

namespace {
    using namespace std;

    TEST(SerializeTest, IntsSerializeTest) { // NOLINT
        std::string str;
        int t, x;

        x = 38457943;
        serialize(x, str, 0);
        deserialize(str, 0, t);
        ASSERT_EQ(t, x);

        str.clear();

        x = -38457943;
        serialize(x, str, 0);
        deserialize(str, 0, t);

        str.clear();

        double z, u = 123.4124;
        serialize(u, str, 0);
        deserialize(str, 0, z);

        ASSERT_EQ(z, u);
    }

    TEST(SerializeTest, PostingNodeSerialTest) { // NOLINT
        PostingNode node(1273, 2934854);
        std::string s = PostingNode::Serialize(node);
        PostingNode fake = PostingNode::Deserialize(s);

        ASSERT_EQ(node.doc_id, fake.doc_id);
        ASSERT_EQ(node.term_freq, fake.term_freq);
    }

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
