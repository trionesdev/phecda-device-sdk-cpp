//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include <phecda/ProtocolDriver.h>
#include <phecda/DeviceServiceSDK.h>

namespace phecda {
    DeviceServiceSDK::DeviceServiceSDK(const std::string &serviceKey, const std::string &serviceVersion,
                                       ProtocolDriver *protocolDriver) {
        this->serviceKey = serviceKey;
        this->serviceVersion = serviceVersion;
        this->protocolDriver = protocolDriver;
    }

    DeviceServiceSDK
    DeviceServiceSDK::newDeviceService(const std::string &serviceKey, const std::string &serviceVersion,
                                       ProtocolDriver *protocolDriver) {
        return {serviceKey, serviceVersion, protocolDriver};
    }

    void DeviceServiceSDK::run() {
        std::cout << "Hello, World! run" << std::endl;
    }
}