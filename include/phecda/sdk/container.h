//
// Created by fengxiaotx on 2024/5/28.
//
#pragma once
#ifndef PHECDA_DEVICE_SDK_CONTAINER_H
#define PHECDA_DEVICE_SDK_CONTAINER_H

#include <string>
#include "config.h"
#include "phecda/bootstrap/di.h"
#include "ProtocolDriver.h"

namespace phecda::sdk {
    std::string configurationName = "configurationStruct";

    ConfigurationStruct configurationFrom(bootstrap::Container *dic) {
        return dic->get<ConfigurationStruct>(configurationName);
    };

    std::string protocolDriverName = "protocolDriver";

    ProtocolDriver protocolDriverFrom(bootstrap::Container *dic) {
        return dic->get<ProtocolDriver>(protocolDriverName);
    }
}

#endif //PHECDA_DEVICE_SDK_CONTAINER_H
