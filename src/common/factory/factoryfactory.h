//
// Created by limo on 12/2/17.
//

#ifndef RAKEMAN_ENGINE_FACTORYFACTORY_H
#define RAKEMAN_ENGINE_FACTORYFACTORY_H

#include <memory>
#include <common/deport.h>
#include "deportfactory.h"

class CFactoryFactory {
public:
    /**
     * @brief Initialize factories. This function should be called before
     * %getInstance gets called.
     */
    static void initialize();
    static std::shared_ptr<CFactoryFactory>& getInstance();

    std::shared_ptr<CFactory<IDeport>> getDeportFactory() {
        return m_deport_factory;
    }

private:
    static std::shared_ptr<CFactoryFactory> m_instance;
    std::shared_ptr<CFactory<IDeport>> m_deport_factory;

};


#endif //RAKEMAN_ENGINE_FACTORYFACTORY_H
