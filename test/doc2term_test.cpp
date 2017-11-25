//
// Created by limo on 17-11-25.
//

#include <string>
#include <iostream>

#include "gtest/gtest.h"
#include "core/tokenizerimpl.h"
#include "core/normalizerimpl.h"
#include "core/doc2term.h"
#include "data/doc.h"

namespace {
    using namespace std;

    /**
     * brief Create a jieba instance
     */
    std::shared_ptr<cppjieba::Jieba> create_jieba() {
        // test resource path
        const char* const DICT_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/jieba.dict.utf8";
        const char* const HMM_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/hmm_model.utf8";
        const char* const USER_DICT_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/user.dict.utf8";
        const char* const IDF_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/idf.utf8";
        const char* const STOP_WORD_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/stop_words.utf8";

        auto p_jieba = std::make_shared<cppjieba::Jieba>(
                DICT_PATH,
                HMM_PATH,
                USER_DICT_PATH,
                IDF_PATH,
                STOP_WORD_PATH
        );
        return p_jieba;
    }

    /**
     * @brief Create a tokenizer instance
     */
    std::shared_ptr<ITokenizer> create_tokenizer() {
        return std::make_shared<CTokenizerImpl>(create_jieba());
    }

    /**
     * @brief Create a normalizer instance
     */
    std::shared_ptr<INormalizer> create_normalizer() {
        return std::make_shared<CNormalizerImpl>();
    }

    /**
     * @brief Create a simple doc which will be used to be termed. And This
     * This doc should be sure that it contains more than 10 tokens since we
     * will check this property in following tests.
     */
    Doc create_a_simple_doc() {
        std::string content = "想要进入“中国天眼”核心观景台，目睹这座庞大"
                "的“天文机器”，所有人需要经过比机场还要严格的安检，包括手机、"
                "相机等在内的电子设备一律寄存，不能随身带入景区，这主要是为了"
                "保护全球最大最强的射电望远镜免受电磁波的干扰";
        return Doc(0, "title", content, "cnn", "http://www.baidu.com");
    }

    TEST(Doc2TermTest, tokenize) { // NOLINT
        auto p_tokenizer = create_tokenizer();
        // todo: need to check if doc has been tokenize correctly
    }

    TEST(Doc2TermTest, normalize) { // NOLINT
        auto p_normalizer = create_normalizer();
        // todo: need to check if tokens has been normalized correctly
    }

    TEST(Doc2TermTest, doc2term) { // NOLINT
        auto p_jieba = create_jieba();
        auto p_tokenizer = create_tokenizer();
        auto p_normalizer = create_normalizer();

        Doc doc = create_a_simple_doc();
        std::vector<Term> terms;
        CDoc2Term doc2Term(p_tokenizer, p_normalizer);
        doc2Term.doc2term(doc, terms);

        std::vector<std::string> str_terms;
        for (auto& term : terms)
            str_terms.push_back(term.term);

        // log here since we have no better method to check if the doc
        // has been termed correctly
        cout << "==> doc-prev: " << doc.content << endl
             << "==> doc-post: " << cppjieba::Join(str_terms.begin(),
                                                   str_terms.end(), "/")
             << endl;

        // make sure this doc has been termed into more than 10 pieces
        // this is a necessary condition
//        ASSERT_GT(terms.size(), 10);
    }

} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
