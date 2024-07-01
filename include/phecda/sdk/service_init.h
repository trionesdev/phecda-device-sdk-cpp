//
// Created by fengxiaotx on 2024/6/4.
//

#ifndef PHECDA_DEVICE_SDK_SERVICE_INIT_H
#define PHECDA_DEVICE_SDK_SERVICE_INIT_H

#include "DeviceServiceSDK.h"
#include "phecda/bootstrap/bootstrap.h"
#include <phecda/sdk/container.h>

namespace phecda::sdk {
    class Bootstrap {
    private:
        DeviceServiceSDK *ds;
    public:
        static std::shared_ptr<Bootstrap> newBootstrap(DeviceServiceSDK *sdk);

        bool bootstrapHandler(const bootstrap::BootstrapHandlerArgs& args);
    };

    class MessagingBootstrap {
    public:
        std::string baseServiceName;

        static std::shared_ptr<MessagingBootstrap> newMessagingBootstrap(const std::string& baseServiceName);

        bool bootstrapHandler(const bootstrap::BootstrapHandlerArgs& args);
    };
}
#endif //PHECDA_DEVICE_SDK_SERVICE_INIT_H
