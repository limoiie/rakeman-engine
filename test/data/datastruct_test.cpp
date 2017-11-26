//
// Created by limo on 17-11-26.
//

#include <map>

#include <gtest/gtest.h>

#include <data/map.h>
#include <data/wrappedstlmap.hpp>

namespace {
    using namespace std;

    TEST(MapTest, operatorAt) { // NOLINT
        auto m = CWrappedStlMap<std::string, std::string>();

        std::string key = "TEST_KEY";
        std::string val = "TEST_VAL";
        std::string invalid_key = "TEST_INVALID_KEY";

        m[key] = val;

        ASSERT_TRUE(m[key] == val);
        ASSERT_TRUE(m[invalid_key].empty());
    }

    TEST(MapTest, insert) { // NOLINT
        auto m = CWrappedStlMap<std::string, std::string>();

        std::string key = "TEST_KEY";
        std::string val = "TEST_VAL";

        std::string key1 = "TEST_KEY1";
        std::string val1 = "TEST_VAL1";

        std::string key2 = "TEST_KEY2";
        std::string val2 = "TEST_VAL2";

        std::string key3 = "TEST_KEY3";
        std::string val3 = "TEST_VAL3";

        m.insert(std::make_pair(key, val));
        m.insert({
                         std::make_pair(key1, val1),
                         std::make_pair(key2, val2),
                         std::make_pair(key3, val3)
                 });

        ASSERT_TRUE(m[key] == val);
        ASSERT_TRUE(m[key1] == val1);
        ASSERT_TRUE(m[key2] == val2);
        ASSERT_TRUE(m[key3] == val3);
    }

    TEST(MapTest, find) { // NOLINT
        auto m = CWrappedStlMap<std::string, std::string>();
        std::string key1 = "TEST_KEY1";
        std::string val1 = "TEST_VAL1";

        std::string key2 = "TEST_KEY2";
        std::string val2 = "TEST_VAL2";

        std::string key3 = "TEST_KEY3";
        std::string val3 = "TEST_VAL3";

        m.insert({
                         std::make_pair(key1, val1),
                         std::make_pair(key2, val2),
                         std::make_pair(key3, val3)
                 });

        auto itr = m.find(key2);

        ASSERT_EQ(itr->second, val2);
    }

    TEST(MapTest, erase) { // NOLINT
        auto m = CWrappedStlMap<std::string, std::string>();

        std::string key1 = "TEST_KEY1";
        std::string val1 = "TEST_VAL1";

        std::string key2 = "TEST_KEY2";
        std::string val2 = "TEST_VAL2";

        std::string key3 = "TEST_KEY3";
        std::string val3 = "TEST_VAL3";

        m.insert({
                         std::make_pair(key1, val1),
                         std::make_pair(key2, val2),
                         std::make_pair(key3, val3)
                 });

        ASSERT_TRUE(m[key1] == val1);
        ASSERT_TRUE(m[key2] == val2);

        m.erase(key1);
        auto itr = m.find(key2);
        m.erase(itr);

        ASSERT_TRUE(m[key1].empty());
        ASSERT_TRUE(m[key2].empty());
    }

    TEST(MapTest, empty) { // NOLINT
        auto m = CWrappedStlMap<std::string, std::string>();
        ASSERT_TRUE(m.empty());

        std::string key = "TEST_KEY";
        std::string val = "TEST_VAL";

        m[key] = val;

        ASSERT_FALSE(m.empty());

        m.erase(key);

        ASSERT_TRUE(m.empty());

    }

    TEST(MapTest, clear) { // NOLINT
        auto m = CWrappedStlMap<std::string, std::string>();

        std::string key1 = "TEST_KEY1";
        std::string val1 = "TEST_VAL1";

        std::string key2 = "TEST_KEY2";
        std::string val2 = "TEST_VAL2";

        std::string key3 = "TEST_KEY3";
        std::string val3 = "TEST_VAL3";

        m.insert({
                         std::make_pair(key1, val1),
                         std::make_pair(key2, val2),
                         std::make_pair(key3, val3)
                 });

        m.clear();

        ASSERT_TRUE(m.empty());
    }

    TEST(MapTest, count) { // NOLINT
        auto m = CWrappedStlMap<std::string, std::string>();

        std::string key = "TEST_KEY";
        std::string val = "TEST_VAL";
        std::string invalid_key = "TEST_INVALID_KEY";

        m[key] = val;

        ASSERT_EQ(m.count(key), static_cast<size_t>(1));
        ASSERT_EQ(m.count(invalid_key), static_cast<size_t>(0));
    }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}