//
// Created by limo on 11/29/17.
//

#ifndef RAKEMAN_ENGINE_SERIALIZER_H
#define RAKEMAN_ENGINE_SERIALIZER_H

#include <string>
#include <list>

typedef char char_t;

template <typename T>
size_t serialize(const T &val, std::string &bits, size_t offset) {
    bits.reserve(offset);
    size_t size_of_val = sizeof(val);
    // todo: remove useless 0 in front of int and NOTE the negative impl
    bits.push_back(static_cast<char_t >(size_of_val));
    for (size_t i = 0; i < size_of_val; ++i) {
        bits.push_back(*((char_t *)(&val) + i));
    }
    return size_of_val + 1;
}

template <typename T>
size_t deserialize(const std::string &bits, size_t offset, T &val) {
    val = 0;
    auto size_of_val = static_cast<size_t>(bits[offset]);
    ++offset;
    for (size_t i = 0; i < size_of_val; ++i) {
        *((char_t *)(&val) + i) = bits[offset+i];
    }
    return size_of_val + 1;
}

#endif //RAKEMAN_ENGINE_SERIALIZER_H
