//
// Created by limo on 11/28/17.
//

#ifndef RAKEMAN_ENGINE_QUERYPROCESS_H
#define RAKEMAN_ENGINE_QUERYPROCESS_H

#include <string>
#include <list>
#include <data/postingsmap.h>
#include <vector>

namespace saker {

    class CQueryExpresser {
    public:
        std::vector<PostingNode> express(const std::string &query);

    private:
        /**
         * Prepare for query processing
         */
        void __prepare();
        /**
         * Scan query and split it into string block and operators which are
         * like +, - and *. If there comes a %stop_c, just return.
         */
        void __scanner(const std::string &query, char stop_c = '\0');
        /**
         * Break the query block which contains no operators but is too big
         * into smaller string block and some meaningful operators.
         */
        void __scanner_breakBlock(std::string &block);

        /**
         * Optimize the syntax structure: remove redundancy string block...
         */
        void __optimal();
        /**
         * Express the syntax structure.
         */
        void __execute();

        void __execute_popAndExecute(std::vector<int>& operates,
                                     std::vector<int>& operands,
                                     std::vector<std::list<PostingNode>>& nodes);

        size_t m_offset;
        // used to store elements included term-index, op-code ...
        std::vector<int> m_elems;
        // used to store terms
        std::vector<std::string> m_terms;
        // used to store the execute result
        std::vector<PostingNode> m_result;

    };

}

#endif //RAKEMAN_ENGINE_QUERYPROCESS_H
