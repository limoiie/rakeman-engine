//
// Created by limo on 11/29/17.
//

#ifndef RAKEMAN_ENGINE_SERIALIZER_H
#define RAKEMAN_ENGINE_SERIALIZER_H

#include <string>
#include <list>
#include <vector>
#include <data/postingsmap.h>
#include <data/doc.h>

typedef char char_t;

/**
 * Implement of Integer family.
 * The format of serialized: num_of_bytes_used_to_store_val|val_memory_bytes
 *
 * @tparam T Integer family: int, size_t, long ...
 * @param val Integer value going to be serialized
 * @param bytes Serialized string container
 * @param offset From where the serialized string should store in container.
 *               NOTE: This param will be updated to the bottom of container.
 * @return Serialize status
 */
/*
template <typename T>
bool serialize(const T &val, std::string &bytes, size_t &offset) {
    // is the reserve right here?
    bytes.reserve(offset);

    // step 1: push a char to take up a place for size which will be set in next
    //         few steps.
    bytes.push_back('0');

    size_t size_of_val = 0;
    T tmp = val > 0 ? val : -val;
    // step 2: copy bytes in memory of val into container from the bottom
    while (tmp != 0) {
        bytes.push_back(static_cast<char_t>(tmp));
        tmp >>= 8;  // 8 bits for one char
        ++size_of_val;
    }

    // step 3: set the size. 1st bit of flag indicates positive or negative,
    //         the last indicates the length of the integer.
    size_t flag = (val > 0 ? 0x00 : 0x80) | size_of_val;
    bytes[offset] = static_cast<char_t>(flag);

    // step 4: update %offset
    offset += size_of_val + 1;  // 1 for the size char which has not been counted in
    return true;
}
*/

/**
 * Implement of Integer family.
 * The format of serialized: num_of_bytes_used_to_store_val|val_memory_bytes
 *
 * @tparam T Integer family: int, size_t, long ...
 * @param val Integer value going to be serialized
 * @param bytes Serialized string container
 * @param offset From where the serialized string should store in container.
 *               NOTE: This param will be updated to the bottom of container.
 * @return Serialize status
 */
template <typename T>
bool serialize(const T &val, std::string &bytes, size_t &offset) {
    // is the reserve right here?
    bytes.reserve(offset);

    // step 1: push a char to take up a place for size which will be set in next
    //         few steps.
    bytes.push_back('0');

    size_t size_of_val = sizeof(T);
    T tmp = val > 0 ? val : -val;
    auto *p_addr = reinterpret_cast<char *>(&tmp);

    // step 2: remove the empty char
    size_t i = size_of_val - 1;
    while (*(p_addr + i) == '\0') {
        if (i == 0) break;
        --i;
    }
    size_of_val = i+1;

    // step 3: copy bytes in memory of val into container from the bottom
    for (size_t k = 0; k < size_of_val; ++k) {
        bytes.push_back(*(p_addr + k));
    }

    // step 4: set the size. 1st bit of flag indicates positive or negative,
    //         the last indicates the length of the integer.
    size_t flag = (val > 0 ? 0x00 : 0x80) | size_of_val;
    bytes[offset] = static_cast<char_t>(flag);

    // step 5: update %offset
    offset += size_of_val + 1;  // 1 for the size char which has not been counted in
    return true;
}

/**
 * Deserialize the Integer family serialized string.
 */
template <typename T>
bool deserialize(const std::string &bytes, size_t &offset, T &val) {
    val = 0;

    // step 1: extract information from the first byte in %bytes
    //         the format of the first type: 1st bit indicates the sign
    //         and remain bits indicate the num of bytes used to store
    //         this integer.
    auto is_negative = static_cast<bool>(bytes[offset] & 0x80);
    auto size_of_val = static_cast<size_t>(bytes[offset] & 0x7F);
    ++offset;

    // step 2: copy memory bytes into %val
    for (size_t i = 0; i < size_of_val; ++i) {
        *((char_t *)(&val) + i) = bytes[offset+i];
    }

    // step 3: update the sign of the val
    if (is_negative) val = -val;

    // step 4: update %offset
    offset += size_of_val;
    return true;
}

/**
 * Specialized implement of %std::string.
 * The format of serialized: serialized_size|std::c_style_string_in_memory
 *
 * @param val The value going to be serialized
 * @param bytes Container used to store the serialized string
 * @param offset From where the serialized should be store in the container.
 *               NOTE: This param will be updated to the bottom of container.
 * @return Serialize status
 */
template <>
inline
bool serialize(const std::string &val, std::string &bytes, size_t &offset) {
    // is the reserve right here?
    bytes.reserve(offset);

    // step 1: serialize size
    size_t size_of_val = val.size();
    serialize(val.size(), bytes, offset);

    // step 2: copy c style string bytes
    for (size_t i = 0; i < size_of_val; ++i) {
        bytes.push_back(val[i]);
    }

    // step 3: update offset
    offset += size_of_val;
    return true;
}

/**
 * Deserialize from %std::string
 */
template <>
inline
bool deserialize(const std::string &bytes, size_t &offset, std::string &val) {
    val.clear();

    // step 1: deserialize size
    size_t size_of_val;
    deserialize(bytes, offset, size_of_val);

    // step 2: copy c style string bytes
    size_t end_of_val = size_of_val + offset;
    for (size_t i = offset; i < end_of_val; ++i) {
        val.push_back(bytes[i]);
    }

    // step 3: update offset
    offset += size_of_val;
    return true;
}

// TODO: This is not the complete version, fix up this if need
template <>
inline
bool serialize(const Doc &val, std::string &bytes, size_t &offset) {
    serialize(val.id, bytes, offset);
    serialize(val.content, bytes, offset);
    return true;
}

// TODO: This is not the complete version, fix up this if need
template <>
inline
bool deserialize(const std::string &bytes, size_t &offset, Doc &val) {
    deserialize(bytes, offset, val.id);
    deserialize(bytes, offset, val.content);
    return true;
}

template <>
inline
bool serialize(const PostingNode &val, std::string &bytes, size_t &offset) {
    serialize(val.doc_id, bytes, offset);
    serialize(val.term_freq, bytes, offset);
    return true;
}

template <>
inline
bool deserialize(const std::string &bytes, size_t &offset, PostingNode &val) {
    deserialize(bytes, offset, val.doc_id);
    deserialize(bytes, offset, val.term_freq);
    return true;
}

template <typename T>
inline
bool serialize(const std::list<T> &val, std::string &bytes, size_t &offset) {
    size_t size_of_val = val.size();
    serialize(size_of_val, bytes, offset);
    for (auto &i : val)
        serialize(i, bytes, offset);
    return true;
}

template <typename T>
inline
bool deserialize(const std::string &bytes, size_t &offset, std::list<T> &val) {
    size_t size_of_val;
    deserialize(bytes, offset, size_of_val);
    for (size_t i = 0; i < size_of_val; ++i) {
        T t;
        deserialize(bytes, offset, t);
        val.push_back(t);
    }
    return false;
}

template <typename T>
inline
bool serialize(const std::vector<T> &val, std::string &bytes, size_t &offset) {
    size_t size_of_val = val.size();
    serialize(size_of_val, bytes, offset);
    for (auto &i : val)
        serialize(i, bytes, offset);
    return true;
}

template <typename T>
inline
bool deserialize(const std::string &bytes, size_t &offset, std::vector<T> &val) {
    size_t size_of_val;
    deserialize(bytes, offset, size_of_val);
    for (size_t i = 0; i < size_of_val; ++i) {
        T t;
        deserialize(bytes, offset, t);
        val.push_back(t);
    }
    return false;
}

#endif //RAKEMAN_ENGINE_SERIALIZER_H
