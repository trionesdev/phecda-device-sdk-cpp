//
// Created by fengxiaotx on 2024/5/28.
//

#ifndef PHECDA_DEVICE_SDK_STARTUP_H
#define PHECDA_DEVICE_SDK_STARTUP_H
#include <string>

namespace phecda::bootstrap {
    class Timer{
    public:
        static Timer* newStartUpTimer(std::string  serviceKey);
    };
}
#endif //PHECDA_DEVICE_SDK_STARTUP_H
