//
// Created by limo on 17-11-28.
//

#ifndef RAKEMAN_ENGINE_POSTINGSOP_H
#define RAKEMAN_ENGINE_POSTINGSOP_H

#include <list>
#include <functional>

using namespace std;

template <typename T>
int Comp(const T& lhv, const T& rhv) {
    if (lhv < rhv) return -1;
    if (lhv > rhv) return 1;
    return 0;
}

template <typename T>
void IntersectLists(const std::list<T> &i_lt1,
                    const std::list<T> &i_lt2,
                    std::list<T> &o_lt3,
                    std::function<int(const T&, const T&)> comp = Comp<T>) {
    auto itr1 = i_lt1.begin();
    auto itr2 = i_lt2.begin();
    while (itr1 != i_lt1.end() && itr2 != i_lt2.end()) {
        if (comp(*itr1, *itr2) < 0) {
            ++itr1;
        } else if (comp(*itr1, *itr2) > 0) {
            ++itr2;
        } else {
            o_lt3.push_back(*itr1);
            ++itr1, ++itr2;
        }
    }
}

template <typename T>
void ConjunctLists(const std::list<T> &i_lt1,
                   const std::list<T> &i_lt2,
                   std::list<T> &o_lt3,
                   std::function<int(const T&, const T&)> comp = Comp<T>) {
    auto itr1 = i_lt1.begin();
    auto itr2 = i_lt2.begin();
    while (itr1 != i_lt1.end() && itr2 != i_lt2.end()) {
        if (comp(*itr1, *itr2) < 0) {
            o_lt3.push_back(*itr1);
            ++itr1;
        } else if (comp(*itr1, *itr2) > 0) {
            o_lt3.push_back(*itr2);
            ++itr2;
        } else {
            o_lt3.push_back(*itr1);
            ++itr1; ++itr2;
        }
    }
    if (itr1 != i_lt1.end())
        o_lt3.insert(o_lt3.end(), itr1, i_lt1.end());
    if (itr2 != i_lt2.end())
        o_lt3.insert(o_lt3.end(), itr2, i_lt2.end());
}

template <typename T>
void ExcludeLists(const std::list<T> &i_src,
                  const std::list<T> &i_exc,
                  std::list<T> &o_tgt,
                  std::function<int(const T&, const T&)> comp = Comp<T>) {
    auto itr1 = i_src.begin();
    auto itr2 = i_exc.begin();
    while (itr1 != i_src.end() && itr2 != i_exc.end()) {
        if (comp(*itr1, *itr2) < 0) {
            o_tgt.push_back(*itr1);
            ++itr1;
        } else if (comp(*itr1, *itr2) > 0) {
            ++itr2;
        } else {
            ++itr1; ++itr2;
        }
    }
    if (itr1 != i_src.end())
        o_tgt.insert(o_tgt.end(), itr1, i_src.end());
}

#endif //RAKEMAN_ENGINE_POSTINGSOP_H
