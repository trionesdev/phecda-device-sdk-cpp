//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include "phecda/sdk/ProtocolDriver.h"

namespace phecda::sdk {
    void bootstrap(std::string args[], const std::string &serviceKey, const std::string &serviceVersion,
                   ProtocolDriver *protocolDriver) {
        std::cout << "Hello, World! bootstrap1" << std::endl;
        DeviceServiceSDK deviceService = DeviceServiceSDK::newDeviceService(serviceKey, serviceVersion, protocolDriver);
        deviceService.run();
    }
}
