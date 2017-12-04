//
// Created by limo on 11/29/17.
//

#include "gtest/gtest.h"

#include <common/deport/deport.h>
#include <common/deport/redisdeport.h>

namespace {
    using namespace std;

    TEST(DeportTest, connect) { // NOLINT
        IDeport *deport = new CRedisDeport("127.0.0.1", 6379);
        ASSERT_TRUE(deport->connect());
    }

    TEST(DeportTest, storeAndFetchPostings) { // NOLINT
        PostingsMap pm;
        pm["word_test"] = {{1, 9, {}}, {7, 101, {}}, {8, 12, {}}, {12, 190, {}}, {15, 230, {}}};
        pm["word_good"] = {{7, 120, {}}, {8, 123, {}}, {9, 1234, {}}, {12, 10, {}}};
        pm["word_down"] = {{12, 49, {}}, {16, 23, {}}, {18, 3, {}}};

        IDeport *deport = new CRedisDeport("127.0.0.1", 6379);
        deport->storePostings(pm);

        PostingsMap pm_fetched;
        pm_fetched = deport->fetchPostings({"word_test", "word_good", "word_down"});

        ASSERT_EQ(pm, pm_fetched);

        // todo: clear all test data from redis
    }
}
