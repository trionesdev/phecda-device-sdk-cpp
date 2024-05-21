//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include <phecda/ProtocolDriver.h>
#include <phecda/DeviceServiceSDK.h>

namespace phecda {
    void bootstrap(std::string args[], const std::string &serviceKey, const std::string &serviceVersion,
                   ProtocolDriver *protocolDriver) {
        std::cout << "Hello, World! bootstrap" << std::endl;
        DeviceServiceSDK deviceService = DeviceServiceSDK::newDeviceService(serviceKey, serviceVersion, protocolDriver);
        deviceService.run();
    }
}