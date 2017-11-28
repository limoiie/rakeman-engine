//
// Created by limo on 17-11-28.
//

#include <string>

#include "gtest/gtest.h"

#include "apps/saker/postingsop.hpp"

namespace {
    using namespace std;

    TEST(PostingsOpTest, IntersectLists) { // NOLINT
        auto list1 = std::list<int>{1, 2, 3, 4};
        auto list2 = std::list<int>{2, 4, 5, 6};
        auto list3 = std::list<int>{2, 4};
        auto list4 = std::list<int>{};

        IntersectLists(list1, list2, list4);

        ASSERT_EQ(list3, list4);
    }

    TEST(PostingsOpTest, ConjunctLists) { // NOLINT
        auto list1 = std::list<int>{1, 2, 3, 4};
        auto list2 = std::list<int>{2, 4, 5, 6};
        auto list3 = std::list<int>{1, 2, 3, 4, 5, 6};
        auto list4 = std::list<int>{};

        ConjunctLists(list1, list2, list4);

        ASSERT_EQ(list3, list4);
    }

    TEST(PostingsOpTest, ExcludeLists) { // NOLINT
        auto list1 = std::list<int>{1, 2, 3, 4};
        auto list2 = std::list<int>{2, 4, 5, 6};
        auto list3 = std::list<int>{1, 3};
        auto list4 = std::list<int>{};

        ExcludeLists(list1, list2, list4);

        ASSERT_EQ(list3, list4);
    }

}