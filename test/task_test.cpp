//
// Created by limo on 12/9/17.
//
#include <string>

#include <common/factory/factoryfactory.h>
#include <common/taskwoker/breakdocblocktask.h>
#include <raker/docindexer.h>
#include <common/taskwoker/sortandmergetempintodicttask.h>

#include "gtest/gtest.h"

namespace {
    using namespace std;

    Doc doc1 = { 10, "", "this is the content of mine", "", ""};
    Doc doc2 = { 11, "", "this is the content of your", "", ""};
    Doc doc3 = { 12, "", "this is not your but mine", "", ""};

    TEST(TastTest, BreakDocBlockTaskTest) { // NOLINT
        std::vector<Doc> docs = {doc1, doc2, doc3};
        CBreakDocBlockTask task = CBreakDocBlockTask(docs);
        task.work();

        auto deport = CFactoryFactory::getInstance()
                ->getDeportFactory()
                ->get(CFactory<IDeport>::DEFAULT);

        std::vector<std::string> terms = {
                "this", "is", "the", "content", "of"
        };
        PostingsMap map;
        deport.get()->fetchPostings(terms, map);
        ASSERT_EQ(map[terms[0]].size(), static_cast<size_t>(3));
        ASSERT_EQ(map[terms[1]].size(), static_cast<size_t>(3));
        ASSERT_EQ(map[terms[2]].size(), static_cast<size_t>(2));
        ASSERT_EQ(map[terms[3]].size(), static_cast<size_t>(2));
        ASSERT_EQ(map[terms[4]].size(), static_cast<size_t>(2));

        deport.get()->deleteTermsInTemp(std::vector<std::string>{
                "this", "is", "the", "not", "your", "but", "mine", "content", "of"
        });
    }

    TEST(TastTest, SortUnsortedPostingListTask) { // NOLINT
        auto deport = CFactoryFactory::getInstance()
                ->getDeportFactory()
                ->get(CFactory<IDeport>::DEFAULT);

        std::string key = "word";
        std::list<PostingNode> nodes = {
                {63},
                {8},
                {52},
                {45},
                {10}
        };
        std::list<PostingNode> sorted_nodes = {
                {8},
                {10},
                {45},
                {52},
                {63},
        };

        PostingsMap map;
        map[key] = nodes;
        deport->appendPostingsToTemp(map);

        auto task = CSortAndMergeTempIntoDictTask(key);
        task.work();

        PostingsMap fake;
        deport->fetchPostings(std::vector<std::string>{key}, fake);
        ASSERT_EQ(sorted_nodes, fake[key]);

        deport->deleteTermsInDict(std::vector<std::string>{key});
    }

}

int main(int argc, char **argv) {
    CFactoryFactory::initialize();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
