//
// Created by fengxiaotx on 2024/5/23.
//

#ifndef PHECDA_DEVICE_SDK_SYSTEM_H
#define PHECDA_DEVICE_SDK_SYSTEM_H
#include <map>
#include <string>

namespace phecda {

    class System {
    public:
        static std::map<std::string, std::string> getEnv();
    };

} // phecda

#endif //PHECDA_DEVICE_SDK_SYSTEM_H
