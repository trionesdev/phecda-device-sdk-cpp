//
// Created by fengxiaotx on 2024/5/28.
//
#ifndef PHECDA_DEVICE_SDK_CONTAINER_H
#define PHECDA_DEVICE_SDK_CONTAINER_H

#include <string>
#include "phecda/sdk/config.h"
#include "phecda/bootstrap/di-container.h"
//#include "ProtocolDriver.h"

namespace phecda::sdk::container {
    class ProtocolDriver;

    static std::string configurationName = "configurationStruct";

    static ConfigurationStruct *configurationFrom(bootstrap::DiContainer *dic) {
        return dic->get<ConfigurationStruct *>(configurationName);
    };

    static std::string protocolDriverName = "protocolDriver";

    static ProtocolDriver *protocolDriverFrom(bootstrap::DiContainer *dic) {
        return dic->get<ProtocolDriver *>(protocolDriverName);
    };
}

#endif //PHECDA_DEVICE_SDK_CONTAINER_H
