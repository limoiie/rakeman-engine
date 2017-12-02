//
// Created by limo on 12/2/17.
//

#include "factoryfactory.h"

std::shared_ptr<CFactoryFactory> CFactoryFactory::m_instance = nullptr;

std::shared_ptr<CFactoryFactory> &CFactoryFactory::getInstance() {
    if (m_instance != nullptr)
        return m_instance;
    throw std::runtime_error("Factory of factory has not been initialized, "
                                     "call initialize() first!");
}

void CFactoryFactory::initialize() {
    auto factory_factory = new CFactoryFactory();

    factory_factory->m_deport_factory
            = std::make_shared<CFactory<IDeport>>("127.0.0.1", 6379);

    m_instance = std::shared_ptr<CFactoryFactory>(factory_factory);
}
