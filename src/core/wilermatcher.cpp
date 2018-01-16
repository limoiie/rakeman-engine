//
// Created by limo on 1/6/18.
//

#include "wilermatcher.h"

#include <iostream>
#include <fstream>
#include <common/string2wstring.h>

bool CWilderMatcher::initialize(const std::string &path){
    std::ifstream data(path);
    if (data.is_open()) {
        std::string word;
        while (!data.eof()) {
            data >> word;
            insert(word);
        }
    } else {
        throw std::runtime_error("Failed to open ind_word file!");
    }
    return true;
}

void CWilderMatcher::insert(const std::string &word) {
    auto temp = String2WString(word) + L"$";
    for (size_t i = 0; i < temp.size(); ++i) {
        __rotate(temp);
        __insert(temp, m_words.size());
    }
    m_words.push_back(word);
}

bool CWilderMatcher::contains(const std::string &word) const {
    return false;
}

void CWilderMatcher::getWordsByPrefix(const std::string &prefix, std::vector<std::string> &words) const {
    auto temp = String2WString(__pattern(prefix));

    const Node *p_curr = &m_root;
    for (auto c : temp) {
        auto itr = p_curr->branches.find(c);
        if (itr == p_curr->branches.end()) {
            return;
        }
        p_curr = &(itr->second);
    }

    __travel(p_curr, words);
}

void CWilderMatcher::__insert(const std::wstring &word, size_t ind_word) {
    Node *p_curr = &m_root;
    for (auto c : word) {
        p_curr = p_curr->createBranchIfNotExist(c);
    }
    p_curr->ind_word = ind_word;
}

void CWilderMatcher::__travel(const Node *p_curr, std::vector<std::string> &words) const {
    if (p_curr->isLeaf()) {
        words.push_back(m_words[p_curr->ind_word]);
    } else {
        for (const auto &itr : p_curr->branches) {
            __travel(&(itr.second), words);
        }
    }
}

void CWilderMatcher::__rotate(std::wstring &word) const {
    if (!word.empty()) {
        auto c = word.front();
        for (size_t i = 1; i < word.size(); ++i)
            word[i-1] = word[i];
        word.back() = c;
    }
}

std::string CWilderMatcher::__pattern(const std::string &str) const {
    std::string ptn;
    size_t itr = str.find('*');
    if (itr <= str.size()) {
        ptn = str.substr(itr + 1, str.size() - itr - 1);
        ptn.push_back('$');
        ptn.append(str.substr(0, itr));
    }
    return ptn;
}
