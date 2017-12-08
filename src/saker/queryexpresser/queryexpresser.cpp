//
// Created by limo on 11/28/17.
//

#include "queryexpresser.h"

#include <common/factory/factoryfactory.h>
#include <data/term.h>
#include <core/termprocess.h>
#include <saker/postingsop.hpp>

static const int k_LT = -5;
static const int k_RT = -4;
static const int k_AD = -3;
static const int k_OR = -2;
static const int k_NT = -1;

std::vector<PostingNode> saker::CQueryExpresser::express(const std::string &query) {
    __prepare();
    __scanner(query);
    __optimal();
    __execute();
    return m_result;
}

void saker::CQueryExpresser::__prepare() {
    m_offset = 0;
    m_result.clear();
    m_elems.clear();
}

void saker::CQueryExpresser::__scanner(const std::string &query, char stop_c) {
    std::string block;
    for (; m_offset < query.size() && stop_c != query[m_offset]; ++m_offset) {
        switch (query[m_offset]) {
            case '(':
                ++m_offset;
                m_elems.push_back(k_LT);
                __scanner(query, ')');
                m_elems.push_back(k_RT);
                break;
            case '*':
                __scanner_breakBlock(block);
                m_elems.push_back(k_AD);
                break;
            case '-':
                __scanner_breakBlock(block);
                m_elems.push_back(k_NT);
                break;
            default:
                block.push_back(query[m_offset]);
        }
    }
    __scanner_breakBlock(block);
}

void saker::CQueryExpresser::__scanner_breakBlock(std::string &block) {
    auto tokenizer = CFactoryFactory::getInstance()
            ->getTokenizerFactory()
            ->get(CFactory<ITokenizer>::ProductType::DEFAULT);
    std::vector<Term> terms, purge_terms;
    // tokenize string to terms which will contains ',.' ...
    tokenizer->tokenize(block, terms);
    // filter out ',.' ...
    filterOutX(terms, purge_terms);

    if (!purge_terms.empty()) {
        if (purge_terms.size() > 1) {
            m_elems.push_back(k_LT);
        }

        m_elems.push_back(static_cast<int>(m_terms.size()));
        m_terms.push_back(purge_terms.front().term);

        for (unsigned int i = 1; i < purge_terms.size(); ++i) {
            m_elems.push_back(k_OR);
            m_elems.push_back(static_cast<int>(m_terms.size()));
            m_terms.push_back(purge_terms[i].term);
        }

        if (purge_terms.size() > 1) {
            m_elems.push_back(k_RT);
        }
    }
    block.clear();
}

void saker::CQueryExpresser::__optimal(){
    // TODO: do optimize stuff -- reduce DNF
    m_elems.insert(m_elems.begin(), k_LT);
    m_elems.push_back(k_RT);
}

void saker::CQueryExpresser::__execute() {
    auto deport = CFactoryFactory::getInstance()
            ->getDeportFactory()
            ->get(CFactory<IDeport>::DEFAULT);
    std::vector<std::list<PostingNode>> nodes;
    deport->fetchPostings(m_terms, nodes);

    std::vector<int> operates, operands;
    for (auto elem : m_elems) {
        switch (elem) {
            case k_RT:
                // pop out of stack for execution until %k_LT
                __execute_popAndExecute(operates, operands, nodes); break;
            case k_LT: case k_AD: case k_OR: case k_NT:
                // push into stack until %k_RT
                operates.push_back(elem); break;
            default:
                operands.push_back(elem);
        }
    }

    // the result'index of execution is stored in the end of operands
    m_result.reserve(nodes[operands.back()].size());
    for (auto &node : nodes[operands.back()]) {
        m_result.push_back(std::move(node));
    }
}

void saker::CQueryExpresser::__execute_popAndExecute(std::vector<int> &operates,
                                                     std::vector<int> &operands,
                                                     std::vector<std::list<PostingNode>>& nodes) {
    while (!operates.empty()) {
        if (operates.back() == k_LT) {
            operates.pop_back();
            return;
        }

        // pop out operands
        int rhv = operands.back();
        operands.pop_back();
        int lhv = operands.back();
        operands.pop_back();

        // push back one empty list used for storing execute result
        nodes.emplace_back();
        // pop out operator and execute
        switch (operates.back()) {
            case k_AD:
                IntersectLists(nodes[lhv], nodes[rhv], nodes.back());
                break;
            case k_OR:
                ConjunctLists(nodes[lhv], nodes[rhv], nodes.back());
                break;
            case k_NT:
                ExcludeLists(nodes[lhv], nodes[rhv], nodes.back());
                break;
            default:
                throw std::runtime_error("Not support operator!");
        }
        operates.pop_back();

        operands.push_back(static_cast<int>(nodes.size() - 1));
    }
}
