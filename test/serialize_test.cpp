//
// Created by limo on 12/1/17.
//

#include <string>
#include <iostream>
#include <data/postingsmap.h>

#include <common/serializer.h>

#include "gtest/gtest.h"

namespace {
    using namespace std;

    TEST(SerializeTest, IntsSerializeTest) { // NOLINT
        std::string str;
        int t, x;
        size_t o, i;
        o = 0, i = 0;

        x = 38457943;
        serialize(x, str, o);
        deserialize(str, i, t);
        ASSERT_EQ(t, x);

        str.clear();
        o = 0, i = 0;

        x = -38457943;
        serialize(x, str, o);
        deserialize(str, i, t);

        str.clear();
        o = 0, i = 0;

        double z, u = 123.4124;
        serialize(u, str, o);
        deserialize(str, i, z);

        ASSERT_EQ(z, u);
    }

    TEST(SerializeTest, PostingNodeSerialTest) { // NOLINT
        PostingNode node(1273, 2934854);
        std::string s = PostingNode::Serialize(node);
        PostingNode fake = PostingNode::Deserialize(s);

        ASSERT_EQ(node.doc_id, fake.doc_id);
        ASSERT_EQ(node.term_freq, fake.term_freq);
    }

    TEST(SerializeTest, StringSerializeTest) { // NOLINT
        std::string sample1 = "This is not my fault! You should make sense.";
        std::string sample2 = "It dose not make any sense! You are a thief.";

        size_t offset = 0;
        std::string container;
        serialize(sample1, container, offset);
        serialize(sample2, container, offset);

        std::string temp;

        offset = 0;
        deserialize(container, offset, temp);
        ASSERT_EQ(temp, sample1);
        deserialize(container, offset, temp);
        ASSERT_EQ(temp, sample2);
    }

    TEST(SerializeTest, DocSerializeTest) { // NOLINT
        Doc doc1 = {123, "", "This is content", "", ""};

        size_t offset = 0;
        std::string container;
        serialize(doc1, container, offset);

        offset = 0;
        Doc fake;
        deserialize(container, offset, fake);

        ASSERT_EQ(doc1, fake);
    }

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
