//
// Created by limo on 12/10/17.
//

#ifndef RAKEMAN_ENGINE_INTEGER2STRING_H
#define RAKEMAN_ENGINE_INTEGER2STRING_H

#include <string>
#include <algorithm>

template <typename T>
std::string Integer2String(T t) {
    std::string container;
    while (t > 0) {
        container.push_back(static_cast<char>('0' + (t%10)));
        t /= 10;
    }
    std::reverse(container.begin(), container.end());
    return container;
}

#endif //RAKEMAN_ENGINE_INTEGER2STRING_H
