//
// Created by fengxiaotx on 2024/6/4.
//

#ifndef PHECDA_DEVICE_SDK_SERVICE_H
#define PHECDA_DEVICE_SDK_SERVICE_H

#include "DeviceServiceSDK.h"
#include "phecda/bootstrap/bootstrap.h"
#include <phecda/sdk/container.h>

namespace phecda::sdk {
    class Bootstrap {
    private:
        DeviceServiceSDK *ds;
    public:
        static Bootstrap* newBootstrap(DeviceServiceSDK *sdk);
        bool bootstrapHandler(bootstrap::BootstrapHandlerArgs args);
    };
}
#endif //PHECDA_DEVICE_SDK_SERVICE_H
