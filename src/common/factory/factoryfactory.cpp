//
// Created by limo on 12/2/17.
//

#include <common/config.h>
#include "factoryfactory.h"

std::shared_ptr<CFactoryFactory> CFactoryFactory::m_instance = nullptr;

const char* const DICT_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/jieba.dict.utf8";
const char* const HMM_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/user.dict.utf8";
const char* const IDF_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/idf.utf8";
const char* const STOP_WORD_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/stop_words.utf8";
const char* const TERMS_PATH = "/home/limo/Projects/clion/rakeman-engine/res/dict/terms";

std::shared_ptr<CFactoryFactory> &CFactoryFactory::getInstance() {
    if (m_instance != nullptr)
        return m_instance;
    throw std::runtime_error("Factory of factory has not been initialized, "
                                     "call initialize() first!");
}

void CFactoryFactory::initialize() {
    auto factory_factory = new CFactoryFactory();

    factory_factory->m_deport_factory
            = std::make_shared<CFactory<IDeport>>(REDIS_ADDRESS, REDIS_PORT);
    factory_factory->m_tokenizer_factory
            = std::make_shared<CFactory<ITokenizer>> (
            DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH
    );

    factory_factory->m_wilder_matcher
            = std::make_shared<CWilderMatcher>();
    factory_factory->m_wilder_matcher->initialize(TERMS_PATH);

    m_instance = std::shared_ptr<CFactoryFactory>(factory_factory);
}
