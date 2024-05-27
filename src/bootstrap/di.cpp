//
// Created by fengxiaotx on 2024/5/22.
//


#include <iostream>
//#include "phecda/bootstrap/di.h"

namespace phecda::bootstrap {

//    template <typename T> Container *Container::newContainer(const std::list<T> &services) {
//        auto container = new Container();
//        container->update(services);
//        return container;
//    }
//
//    template <typename T> void Container::update(const std::list<T> &services) {
//        for (auto &service: services) {
//            auto name = typeid(service).name();
//            std::cout << typeid(service).name() << std::endl;
//            serviceMap[name] = service;
//        }
//    }
//
//    template <typename T> T Container::get() {
//        return serviceMap[typeid(T).name()];
//    }
//
//    template<typename T>
//    void Container::registerService( T &service) {
//        std::cout << typeid(service).name() << std::endl;
//        std::cout << std::type_index(typeid(service)).name() << std::endl;
//        serviceMap["ssd"] = 1;
//        serviceMap["ss"] = 1;
//        serviceMap["ssd3"] = 1;
//        std::cout << "s" << std::endl;
//    }
//
//    void Container::sss(std::any aa) {
//        std::cout << "sss"<< typeid(aa).name() << std::endl;
//    }
}
