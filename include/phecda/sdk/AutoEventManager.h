//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_AUTOEVENTMANAGER_H
#define PHECDA_DEVICE_AUTOEVENTMANAGER_H

#include <string>

namespace phecda {
    class AutoEventManager {
    public:
        virtual void startAutoEvents();
        virtual void restartForDevice(std::string name);
        virtual void stopForDevice(std::string deviceName);
    };
}
#endif //PHECDA_DEVICE_AUTOEVENTMANAGER_H
