//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_DEPORTFACTORY_H
#define RAKEMAN_ENGINE_DEPORTFACTORY_H

#include <common/factory/factory.h>
#include <common/deport/deport.h>
#include <common/deport/redisdeport.h>

#include <utility>

// should be singleton?
template <>
class CFactory<IDeport> {
public:
    CFactory(const std::string &default_host,
             size_t default_port) {
        m_default = std::make_shared<CRedisDeport>(default_host, default_port);
    }

    enum ProductType {
        DEFAULT,
        REMOTE,
        LOCAL
    };

    std::shared_ptr<IDeport> get(ProductType type) {
        switch (type) {
            case DEFAULT:
                return m_default;
            case REMOTE:
            case LOCAL:
            default:
                throw std::runtime_error("No impl for this product!");
        }
    }

private:
    std::shared_ptr<IDeport> m_default;

};

#endif //RAKEMAN_ENGINE_DEPORTFACTORY_H
