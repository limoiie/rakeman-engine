//
// Created by limo on 17-11-26.
//

#ifndef RAKEMAN_ENGINE_TRIEMAP_H
#define RAKEMAN_ENGINE_TRIEMAP_H


#include <map>
#include "map.h"

/**
 * @brief This is just a temp implement of map used in %PostingsMap, consider
 * constructing a TrieMap to replace this class in %PostingsMap
 */
template <typename K, typename V>
class CWrappedStlMap : public IMap<K, V, typename std::map<K, V>::iterator> {
public:
    typedef IMap<K, V, typename std::map<K, V>::iterator> base_map;
    typedef typename base_map::val_type val_type;
    typedef typename base_map::key_type key_type;
    typedef typename base_map::item_type item_type;
    typedef typename base_map::iterator iterator;
    typedef typename base_map::size_type size_type;

    ~CWrappedStlMap() override = default;

    val_type &operator[](const key_type &i_key) override {
        return m_proxy[i_key];
    }

    val_type &operator[](key_type &&i_key) override {
        return m_proxy[std::move(i_key)];
    }

    std::pair<iterator, bool> insert(const item_type &i_val) override {
        return m_proxy.insert(i_val);
    }

    void insert(std::initializer_list<item_type> i_list) override {
        m_proxy.insert(i_list);
    }

    iterator erase(iterator i_pos) override {
        return m_proxy.erase(i_pos);
    }

    size_type erase(const key_type &i_key) override {
        return m_proxy.erase(i_key);
    }

    iterator begin() {
        return m_proxy.begin();
    }

    iterator end() {
        return m_proxy.end();
    }

    bool empty() const override {
        return m_proxy.empty();
    }

    void clear() override {
        m_proxy.clear();
    }

    iterator find(const key_type &i_key) override {
        return m_proxy.find(i_key);
    }

    size_type count(const key_type &i_key) const override {
        return m_proxy.count(i_key);
    }

private:
    std::map<K, V> m_proxy;

};

#endif //RAKEMAN_ENGINE_TRIEMAP_H
