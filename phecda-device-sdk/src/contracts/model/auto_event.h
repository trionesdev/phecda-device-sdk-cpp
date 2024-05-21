//
// Created by fengxiaotx on 2024/5/21.
//

#ifndef PHECDA_DEVICE_AUTO_EVENT_H
#define PHECDA_DEVICE_AUTO_EVENT_H


#include <string>

namespace phecda {
    class AutoEvent {
    public:
        std::string interval;
        bool onChange;
        std::string sourceName;
    };
}


#endif //PHECDA_DEVICE_AUTO_EVENT_H
