//
// Created by fengxiaotx on 2024/5/21.
//

#ifndef PHECDA_DEVICE_SDK_APP_PRPTOCOLDRIVER_H
#define PHECDA_DEVICE_SDK_APP_PRPTOCOLDRIVER_H

#include <phecda/sdk/DeviceServiceSDK.h>

namespace phecda::sdk {
//    class DeviceServiceSDK;
    class ProtocolDriver {
    public:
        void initialize(DeviceServiceSDK *sdk);
        void start();
    };
}
#endif //PHECDA_DEVICE_SDK_APP_PRPTOCOLDRIVER_H
