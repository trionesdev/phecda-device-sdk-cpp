//
// Created by Bane Shi on 2024/3/7.
//

#include <stdexcept>
#include <iostream>
#include "device_service_sdk.h"

namespace phecda {
    DeviceService DeviceService::newDeviceService(const std::string& serviceKey, const std::string& serviceVersion, ProtocolDriver *protocolDrive) {
        return {serviceKey, serviceVersion, protocolDrive};
    }

    DeviceService::DeviceService(const std::string& serviceKey, const std::string& serviceVersion, ProtocolDriver *protocolDrive) {
        if (serviceKey.empty()) {
            throw std::invalid_argument("please specify device service name");
        }
        if (serviceVersion.empty()) {
            throw std::invalid_argument("please specify device service version");
        }
        this->serviceKey = serviceKey;
        this->baseServiceName = serviceVersion;
        this->protocolDriver = protocolDrive;
    }

    std::string DeviceService::addDevice(const Device& device) {
        return "";
    }

    void DeviceService::run() {
        std::cout << "Hello, World! run" << std::endl;
    }

    DeviceService::~DeviceService() {

    }



} // phecda