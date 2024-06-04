//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_DI_H
#define PHECDA_DEVICE_DI_H

#include <map>
#include <string>
#include <any>
#include <mutex>
#include <list>
#include <typeindex>

namespace phecda::bootstrap {

    typedef std::map<std::string, std::any> ServiceConstructorMap;

    class DiContainer {
    private:
        std::map<std::string, std::any> serviceMap;
        std::mutex mutex;
    public:
        static DiContainer *newContainer(const ServiceConstructorMap &services) {
            auto *container = new DiContainer();
            for (const auto &service: services) {
                container->serviceMap[service.first] = service.second;
            }
            return container;
        };

        void update(const ServiceConstructorMap &services) {
            for (const auto &service: services) {
                serviceMap[service.first] = service.second;
            }
        };

        template<typename T>
        T get(std::string name) {
            return std::any_cast<T>(serviceMap[name]);
        };

    };


}
#endif //PHECDA_DEVICE_DI_H
