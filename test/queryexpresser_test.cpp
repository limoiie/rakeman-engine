//
// Created by limo on 12/2/17.
//

#include <string>
#include <iostream>

#include <common/serializer.h>
#include <common/factory/factory.h>
#include <common/factory/deportfactory.h>
#include <common/factory/factoryfactory.h>

#include <saker/queryexpresser/queryexpresser.h>

#include "gtest/gtest.h"

namespace {
    using namespace std;
    using namespace saker;

    TEST(QueryExpresserTests, CQueryExpresser) { // NOLINT
        auto deport = CFactoryFactory::getInstance()
                ->getDeportFactory()
                ->get(CFactory<IDeport>::DEFAULT);

        // prepare the query string
        std::string query_string = "(tomas * like * (potato + tomato))-dislike";
        // prepare the test samples
        std::vector<std::pair<std::string, std::list<PostingNode>>> test_samples = {
                {"tomas",   {{1}, {3}, {5}, {6}, {9}}},
                {"like",    {{1}, {3}, {4}, {5}, {6}}},
                {"potato",  {{3}, {5}, {10}, {13}, {14}}},
                {"tomato",  {{1}, {4}, {6}, {7}, {9}}},
                {"dislike", {{0}, {2}, {4}, {6}, {14}}},
        };

        PostingsMap map;
        // store test samples into deport
        for (const auto &sample_pair : test_samples) {
            map[sample_pair.first] = sample_pair.second;
        }
        deport->storePostingsInDict(map);

        CQueryExpresser express;
        auto nodes = express.express(query_string);
        ASSERT_EQ(nodes.size(), static_cast<size_t>(3));
        ASSERT_EQ(nodes[0].doc_id, 1);
        ASSERT_EQ(nodes[1].doc_id, 3);
        ASSERT_EQ(nodes[2].doc_id, 5);

        // delete test data after test
        deport->deleteTermsInTemp({"tomas", "like", "potato", "tomato", "dislike"});
    }
}

int main(int argc, char **argv) {
    CFactoryFactory::initialize();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
