//
// Created by limo on 1/6/18.
//

#ifndef RAKEMAN_ENGINE_WILDMATCHER_H
#define RAKEMAN_ENGINE_WILDMATCHER_H

#include <string>
#include <vector>
#include <set>
#include <map>

class CWilderMatcher {
public:
    bool initialize(const std::string& path);
    void insert(const std::string& word);
    bool contains(const std::string& word) const;
    void getWordsByPrefix(const std::string& prefix,std::vector<std::string> &words) const;

private:
    struct Node {
        std::map<wchar_t, Node> branches;
        size_t ind_word;

        inline Node *createBranchIfNotExist(wchar_t c) {
            return &branches[c];
        }

        inline bool isLeaf() const {
            return branches.empty();
        }
    };

    std::string __pattern(const std::string &str) const;

    void __insert(const std::wstring& word, size_t ind_word);
    void __travel(const Node *p_curr, std::vector<std::string> &words) const;
    void __rotate(std::wstring& word) const;

    Node m_root;
    std::vector<std::string> m_words;
};


#endif //RAKEMAN_ENGINE_WILDMATCHER_H
