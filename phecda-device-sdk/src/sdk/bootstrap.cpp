//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include "../phecda_device_sdk.h"
#include "device_service_sdk.h"

namespace phecda {
    void bootstrap(std::string args[], const std::string& serviceKey, const std::string& serviceVersion, ProtocolDriver *protocolDriver) {
        std::cout << "Hello, World! bootstrap" << std::endl;
//        DeviceService deviceService = DeviceService::newDeviceService(serviceKey, serviceVersion, protocolDriver);
//        deviceService.run();
    }
}