//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_CONTAINER_H
#define PHECDA_DEVICE_CONTAINER_H

#include <map>
#include <string>
#include <any>
#include <mutex>
#include <list>
#include <typeindex>

namespace phecda::bootstrap {

    typedef struct ClassType {
    };

    class Container {
    private:
        std::map<std::string, std::any> serviceMap;
        std::mutex mutex;
    public:
        template<typename T>
        static Container *newContainer(const std::list<T> &services) {
            auto *container = new Container();
            for (auto &service : services) {
                container->serviceMap[typeid(service).name()] = service;
                std::cout << typeid(service).name() << std::endl;
            }
            return container;
        };

        template<typename T>
        void registerService(T &service) {};

        template<typename T>
        void update(const std::list<T> &services) {};

        template<typename T>
        T get() {};

        template<typename T>
        void sss(ClassType aa) {};

    };


}
#endif //PHECDA_DEVICE_CONTAINER_H
