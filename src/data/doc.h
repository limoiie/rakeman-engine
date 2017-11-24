//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_DOC_H
#define RAKEMAN_ENGINE_DOC_H

#include <string>
#include <utility>

/*
 * @brief Doc contains strings of a document. Doc will be constructed with info
 * fetched from db.
 */
struct Doc {
    long long int id;
    std::string title;
    std::string content;
    std::string source;
    std::string url;

    explicit Doc(long long int i_id,
                 std::string i_title,
                 std::string i_content,
                 std::string i_source,
                 std::string i_url)
            : id(i_id),
              title(std::move(i_title)),
              content(std::move(i_content)),
              source(std::move(i_source)),
              url(std::move(i_url)) {}
};

#endif //RAKEMAN_ENGINE_DOC_H
