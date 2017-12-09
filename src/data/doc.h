//
// Created by limo on 2017/11/24.
//

#ifndef RAKEMAN_ENGINE_DOC_H
#define RAKEMAN_ENGINE_DOC_H

#include <string>
#include <utility>

typedef long long int doc_id_t;

/*
 * @brief Doc contains strings of a document. Doc will be constructed with info
 * fetched from db.
 */
struct Doc {
    doc_id_t id;
    std::string title;
    std::string content;
    std::string source;
    std::string url;

    Doc()
            : id(-1),
              title(),
              content(),
              source(),
              url() {
        // empty
    }

    Doc(doc_id_t i_id,
        std::string i_title,
        std::string i_content,
        std::string i_source,
        std::string i_url)
            : id(i_id),
              title(std::move(i_title)),
              content(std::move(i_content)),
              source(std::move(i_source)),
              url(std::move(i_url)) {
        // empty
    }

    bool operator==(const Doc &rhs) const {
        return id == rhs.id &&
               title == rhs.title &&
               content == rhs.content;
    }

    bool operator!=(const Doc &rhs) const {
        return !(rhs == *this);
    }

};

// TODO: This is not the complete version, fix up this if need
template <>
bool serialize<Doc>(const Doc &val, std::string &bytes, size_t &offset) {
    serialize(val.id, bytes, offset);
    serialize(val.content, bytes, offset);
    return true;
}

// TODO: This is not the complete version, fix up this if need
template <>
bool deserialize<Doc>(const std::string &bytes, size_t &offset, Doc &doc) {
    deserialize(bytes, offset, doc.id);
    deserialize(bytes, offset, doc.content);
    return true;
}

#endif //RAKEMAN_ENGINE_DOC_H
