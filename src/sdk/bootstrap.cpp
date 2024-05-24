//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include <phecda/ProtocolDriver.h>
#include <phecda/bootstrap/args/CommonArgs.h>
#include <phecda/Args.h>
#include "../bootstrap/args/Args.cpp"

namespace phecda {
    void bootstrap(std::string args[], const std::string &serviceKey, const std::string &serviceVersion,
                   ProtocolDriver *protocolDriver) {
        std::cout << "Hello, World! bootstrap1" << std::endl;
        CommonArgs::withUsage(":");
        Args::ss();
        DeviceServiceSDK deviceService = DeviceServiceSDK::newDeviceService(serviceKey, serviceVersion, protocolDriver);
        deviceService.run();
    }
}