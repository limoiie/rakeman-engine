//
// Created by limo on 11/28/17.
//

#include "queryexpresser.h"

#include <common/factory/factoryfactory.h>
#include <data/term.h>
#include <core/termprocess.h>
#include <saker/postingsop.h>

static const char c_LM = '[';
static const char c_RM = ']';
static const char c_LT = '(';
static const char c_RT = ')';
static const char c_AD = '^';
static const char c_OR = '|';
static const char c_NT = '-';

static const int k_LT = -5;
static const int k_RT = -4;
static const int k_AD = -3;
static const int k_OR = -2;
static const int k_NT = -1;

std::vector<doc_id_t> saker::CQueryExpresser::express(const std::string &query) {
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
    m_terms.clear();
}

void saker::CQueryExpresser::__scanner(const std::string &query, char stop_c) {
    size_t offset = m_offset;
    while (m_offset < query.size() && stop_c != query[m_offset]) {
        switch (query[m_offset]) {
            case c_LM:
                offset = ++m_offset;
                while (query[m_offset] != c_RM) ++m_offset;
                __scanner_wildMatcher(query.substr(offset, m_offset-offset));
                break;
            case c_LT:
                ++m_offset;
                m_elems.push_back(k_LT);
                __scanner(query, c_RT);
                m_elems.push_back(k_RT);
                break;
            case c_AD:
                __scanner_breakBlock(query.substr(offset, m_offset-offset));
                m_elems.push_back(k_AD);
                break;
            case c_NT:
                __scanner_breakBlock(query.substr(offset, m_offset-offset));
                m_elems.push_back(k_NT);
                break;
            default:
                ++m_offset;
                continue;
        }
        offset = ++m_offset;
    }
    __scanner_breakBlock(query.substr(offset, m_offset-offset));
}

void saker::CQueryExpresser::__scanner_breakBlock(const std::string &block) {
    if (block.empty()) return;

    auto tokenizer = CFactoryFactory::getInstance()
            ->getTokenizerFactory()
            ->get(CFactory<ITokenizer>::ProductType::DEFAULT);
    std::vector<Term> terms;
    // tokenize string to terms which will contains ',.' ...
    tokenizer->tokenize(block, terms);
    // filter out ',.' ...
    filterOutX(terms);

    if (!terms.empty()) {
        if (terms.size() > 1) {
            m_elems.push_back(k_LT);
        }

        m_elems.push_back(static_cast<int>(m_terms.size()));
        m_terms.push_back(terms.front().term);

        for (unsigned int i = 1; i < terms.size(); ++i) {
            m_elems.push_back(k_OR);
            m_elems.push_back(static_cast<int>(m_terms.size()));
            m_terms.push_back(terms[i].term);
        }

        if (terms.size() > 1) {
            m_elems.push_back(k_RT);
        }
    } else { // ugly repair
        m_elems.push_back(static_cast<int>(m_terms.size()));
        m_terms.push_back("中国");
    }
}

void saker::CQueryExpresser::__scanner_wildMatcher(const std::string &str) {
    auto wilderMatcher = CFactoryFactory::getInstance()
            ->getWilderMatcher();

    std::vector<std::string> terms;
    wilderMatcher->getWordsByPrefix(str, terms);

    if (!terms.empty()) {
        if (terms.size() > 1) {
            m_elems.push_back(k_LT);
        }

        m_elems.push_back(static_cast<int>(m_terms.size()));
        m_terms.push_back(terms.front());

        for (unsigned int i = 1; i < terms.size(); ++i) {
            m_elems.push_back(k_OR);
            m_elems.push_back(static_cast<int>(m_terms.size()));
            m_terms.push_back(terms[i]);
        }

        if (terms.size() > 1) {
            m_elems.push_back(k_RT);
        }
    } else { // ugly repair
        m_elems.push_back(static_cast<int>(m_terms.size()));
        m_terms.push_back("中国");
    }
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

    // step 1: fetch posting list by terms
    std::vector<std::list<PostingNode>> nodes;
    deport->fetchPostings(m_terms, nodes);

    // step 3: initialize term-set flag which is used for tagging
    // terms-collection in each posting node
    InitWfIdf(nodes, deport->countDocs());

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
    // sort the result list
    SortDocNodesByWfIdf(nodes[operands.back()], m_result);
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
            case k_AD: IntersectLists(nodes[lhv], nodes[rhv], nodes.back()); break;
            case k_OR: ConjunctLists(nodes[lhv], nodes[rhv], nodes.back()); break;
            case k_NT: ExcludeLists(nodes[lhv], nodes[rhv], nodes.back()); break;
            default:
                throw std::runtime_error("Not support operator!");
        }
        operates.pop_back();

        operands.push_back(static_cast<int>(nodes.size() - 1));
    }
}
