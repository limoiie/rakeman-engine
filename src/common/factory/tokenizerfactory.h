//
// Created by limo on 12/3/17.
//

#ifndef RAKEMAN_ENGINE_TOKENIZERFACTORY_H
#define RAKEMAN_ENGINE_TOKENIZERFACTORY_H

#include <string>

#include <core/tokenizer.h>
#include <cppjieba/Jieba.hpp>
#include <memory>
#include <core/tokenizerimpl.h>

template <>
class CFactory<ITokenizer> {
public:
    enum ProductType {
        DEFAULT,
    };

    CFactory(const std::string &dict_path,
             const std::string &hmm_path,
             const std::string &user_dict_path,
             const std::string &idf_path,
             const std::string &stop_word_path) {
        auto p_jieba = std::make_shared<cppjieba::Jieba>(
                dict_path, hmm_path, user_dict_path, idf_path, stop_word_path
        );
        m_default = std::make_shared<CTokenizerImpl>(p_jieba);
    }

    std::shared_ptr<ITokenizer> get(ProductType type) {
        switch (type) {
            case DEFAULT:
                return m_default;
            default:
                throw std::runtime_error("No impl for this product!");
        }
    }

private:
    std::shared_ptr<ITokenizer> m_default;

};

#endif //RAKEMAN_ENGINE_TOKENIZERFACTORY_H
