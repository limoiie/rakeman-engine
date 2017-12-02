//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_FACTORY_H
#define RAKEMAN_ENGINE_FACTORY_H

#include <stdexcept>
#include <memory>

template <typename P>
class CFactory {
public:
    enum ProductType {};

    std::shared_ptr<P> get(ProductType type) {
        throw std::runtime_error("No impl for this factory");
    }

};

#endif //RAKEMAN_ENGINE_FACTORY_H
