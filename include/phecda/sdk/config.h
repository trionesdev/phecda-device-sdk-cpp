//
// Created by fengxiaotx on 2024/5/22.
//
#pragma once
#ifndef PHECDA_DEVICE_CONFIG_H
#define PHECDA_DEVICE_CONFIG_H

#include <string>
#include <map>
#include "phecda/bootstrap/interfaces.h"

namespace phecda::sdk {

    struct DeviceInfo {
        bool dataTransform = false;
        int maxCmdOps = 0;
        std::string profilesDir;
        std::string devicesDir;
        bool enableAsyncReadings;
    };

    struct MqttInfo {
        std::string clientId;
        std::string protocol;
        std::string host;
    };

    struct ConfigurationStruct : public bootstrap::Configuration {
        long MaxEventSize;
        DeviceInfo device;
        std::map<std::string, std::string> driver;
        MqttInfo mqtt;
    };
}
#endif //PHECDA_DEVICE_CONFIG_H
