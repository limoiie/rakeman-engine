//
// Created by limo on 1/8/18.
//

#include <memory>

#include <core/wilermatcher.h>
#include <common/factory/factoryfactory.h>

using namespace std;

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

int main() {
    /*
    CFactoryFactory::initialize();
    saker::CQueryExpresser expresser;
    string sentence;
    while (true) {
        cout << "Please input sentence: " << endl;
        if (cin >> sentence) {
            auto res = expresser.express(sentence);
            cout << "Hit news " << res.size() << endl;
        } else break;
    }
     */
    auto p_jieba = create_jieba();

    string sentence;
    while (true) {
        cout << "Please input sentence: " << endl;
        if (cin >> sentence) {
            vector<pair<string, string>> words;
            p_jieba->Tag(sentence, words);
            for (const auto &word : words) {
                cout << word.first << ": " << word.second << endl;
            }
        } else break;
    }
    return 0;
}
