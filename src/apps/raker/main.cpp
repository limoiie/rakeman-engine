#include <thread>
#include <cppjieba/Jieba.hpp>

#include "../../core/tokenizer.h"
#include "../../core/tokenizerimpl.h"
#include "../../core/normalizer.h"
#include "../../core/normalizerimpl.h"
#include "../../data/doc.h"
#include "../../core/doc2term.h"

const char* const DICT_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/jieba.dict.utf8";
const char* const HMM_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/user.dict.utf8";
const char* const IDF_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/idf.utf8";
const char* const STOP_WORD_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/stop_words.utf8";

using namespace std;

int main() {
    auto p_jieba = make_shared<cppjieba::Jieba>(
            DICT_PATH,
            HMM_PATH,
            USER_DICT_PATH,
            IDF_PATH,
            STOP_WORD_PATH
    );

    std::shared_ptr<ITokenizer> p_tokenizer
            = make_shared<CTokenizerImpl>(p_jieba);
    std::shared_ptr<INormalizer> p_normalizer
            = make_shared<CNormalizerImpl>();

    CDoc2Term doc2Term(p_tokenizer, p_normalizer);

    std::vector<Term> terms;
    string content = "想要进入“中国天眼”核心观景台，目睹这座庞大的“"
            "天文机器”，所有人需要经过比机场还要严格的安检，包括手机、"
            "相机等在内的电子设备一律寄存，不能随身带入景区，这主要是为"
            "了保护全球最大最强的射电望远镜免受电磁波的干扰";
    Doc doc = Doc(0,
                  "title",
                  content,
                  "cnn",
                  "http://www.baidu.com"
    );

    doc2Term.doc2term(doc, terms);
    for (auto term : terms)
        cout << term.term << endl;

    cout << "FINISHED" << endl;
    return 0;
}