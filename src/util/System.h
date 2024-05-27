//
// Created by fengxiaotx on 2024/5/23.
//

#ifndef PHECDA_DEVICE_SDK_SYSTEM_H
#define PHECDA_DEVICE_SDK_SYSTEM_H
#include <map>
#include <string>

namespace phecda::util {

    class System {
    public:
        static std::map<std::string, std::string> getEnv();
        static std::string getEnv(const std::string& key);
    };

} // phecda

#endif //PHECDA_DEVICE_SDK_SYSTEM_H
