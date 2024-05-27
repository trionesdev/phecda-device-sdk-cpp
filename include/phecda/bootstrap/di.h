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

namespace phecda::bootstrap {

    class Container {

    private:
        std::map<std::string, std::any> serviceMap = {};
        std::mutex mutex;
    public:

        static Container *newContainer(const std::list<std::any> &services);

        void update(const std::list<std::any> &services);

        template<typename T> T& get();
    };
}
#endif //PHECDA_DEVICE_CONTAINER_H
