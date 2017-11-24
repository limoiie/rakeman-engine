#include <iostream>
#include <fstream>

#include "cppjieba/Jieba.hpp"

const char* const DICT_PATH = "D:/Project/remote/cpp/rakeman-engine/res/dict/jieba.dict.utf8";
const char* const HMM_PATH = "D:/Project/remote/cpp/rakeman-engine/res/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "D:/Project/remote/cpp/rakeman-engine/res/dict/user.dict.utf8";
const char* const IDF_PATH = "D:/Project/remote/cpp/rakeman-engine/res/dict/idf.utf8";
const char* const STOP_WORD_PATH = "D:/Project/remote/cpp/rakeman-engine/res/dict/stop_words.utf8";

using namespace std;

void process(cppjieba::Jieba &jieba, const string &k_str, int num) {
    vector<string> tokens;
    for (int i = 0; i < num; ++i) {
        jieba.CutForSearch(k_str, tokens, true);
    }
}


int main() {
    cppjieba::Jieba jieba(
            DICT_PATH,
            HMM_PATH,
            USER_DICT_PATH,
            IDF_PATH,
            STOP_WORD_PATH
    );

    string str_need_split = "Hello, world! This is limo";
    vector<string> tokens;

    time_t start_pt = time(nullptr);
    for (int i = 0; i < 100000; ++i) {
        jieba.CutForSearch(str_need_split, tokens, true);
    }
    cout << "COST: " << (time(nullptr) - start_pt) << endl;

    return 0;
}