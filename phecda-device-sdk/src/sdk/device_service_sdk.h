//
// Created by Bane Shi on 2024/3/7.
//

#ifndef DEVICE_SERVICE_SDK_H
#define DEVICE_SERVICE_SDK_H

#include <string>
#include "../phecda_device_sdk.h"
#include "../contracts/model/device.h"

namespace phecda {

    class DeviceService {
    private:
        std::string serviceKey;
        std::string baseServiceName;
        ProtocolDriver *protocolDriver;
    public:
        DeviceService(const std::string& serviceKey, const std::string& serviceVersion, ProtocolDriver *protocolDriver);

        static DeviceService newDeviceService(const std::string& serviceKey, const std::string& serviceVersion, ProtocolDriver *protocolDriver);

        std::string addDevice(const Device& device);
        void run();
        ~DeviceService();
    };

} // phecda

#endif //DEVICE_SERVICE_SDK_H
