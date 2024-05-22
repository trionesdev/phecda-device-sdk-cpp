//
// Created by fengxiaotx on 2024/5/22.
//
#include <phecda/bootstrap/di/Container.h>

namespace phecda {

    void Container::update(std::list<std::any> services) {
        for (auto &service: services) {
            auto name = typeid(service).name();
            serviceMap[name] = service;
        }
    }



}