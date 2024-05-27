//
// Created by fengxiaotx on 2024/5/22.
//


#include "phecda/bootstrap/di.h"

namespace phecda::bootstrap
{

    Container* Container::newContainer(const std::list<std::any>& services)
    {
        auto container = new Container();
        container->update(services);
        return container;
    }

    void Container::update(const std::list<std::any>& services)
    {
        for (auto& service : services)
        {
            auto name = typeid(service).name();
            serviceMap[name] = service;
        }
    }

    template<typename T> T& Container::get() {
        return serviceMap[typeid(T).name()];
    }
}
