//
// Created by fengxiaotx on 2024/5/21.
//

#ifndef PHECDA_DEVICE_SDK_CPP_DEVICESDK_H
#define PHECDA_DEVICE_SDK_CPP_DEVICESDK_H

#include <string>

namespace phecda {
    class ProtocolDriver;  //向前申明
    class DeviceServiceSDK {
    private:
        std::string serviceVersion;
        std::string serviceKey;
        std::string baseServiceName;
        ProtocolDriver *protocolDriver;
    public:
        DeviceServiceSDK(const std::string &serviceKey, const std::string &serviceVersion,
                         ProtocolDriver *protocolDriver);

        static DeviceServiceSDK newDeviceService(const std::string &serviceKey, const std::string &serviceVersion,
                                                 ProtocolDriver *protocolDriver);

        void run();
    };


}
#endif //PHECDA_DEVICE_SDK_CPP_DEVICESDK_H
