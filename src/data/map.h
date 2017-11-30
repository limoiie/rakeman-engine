//
// Created by limo on 17-11-26.
//

#ifndef RAKEMAN_ENGINE_MAP_H
#define RAKEMAN_ENGINE_MAP_H

#include <utility>
#include <cstdio>

// todo: key comparison, value comparison, const iterator ...
template <typename K, typename V, typename I>
class IMap {
public:
    typedef V val_type;
    typedef K key_type;
    typedef std::pair<const key_type, val_type> item_type;
    typedef I iterator;
    typedef size_t size_type;

    virtual val_type& operator[](const key_type& i_key) = 0;
    virtual val_type& operator[](key_type&& i_key) = 0;

    virtual std::pair<iterator, bool> insert(const item_type& i_val) = 0;
    virtual void insert(std::initializer_list<item_type> i_list) = 0;

    virtual iterator erase(iterator i_pos) = 0;
    virtual size_type erase(const key_type& i_key) = 0;

    virtual iterator find(const key_type& i_key) = 0;
    virtual size_type count(const key_type& i_key) const = 0;

    virtual iterator begin() = 0;
    virtual iterator end() = 0;

    virtual bool empty() const = 0;
    virtual void clear() = 0;

    virtual ~IMap() = default;

};

#endif //RAKEMAN_ENGINE_MAP_H
