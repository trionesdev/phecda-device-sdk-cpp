//
// Created by fengxiaotx on 2024/5/28.
//
#ifndef PHECDA_DEVICE_SDK_CONTAINER_H
#define PHECDA_DEVICE_SDK_CONTAINER_H

#include <string>
#include "phecda/sdk/config.h"
#include "phecda/sdk/auto_event.h"
#include "phecda/bootstrap/di_container.h"
#include <phecda/sdk/ProtocolDriver.h>
#include <phecda/sdk/messaging.h>

namespace phecda::sdk::container {
//    class ProtocolDriver;

    static std::string configurationName = "configurationStruct";

    static std::shared_ptr<ConfigurationStruct> configurationFrom(const std::shared_ptr<bootstrap::DiContainer>& dic) {
        return dic->get<std::shared_ptr<ConfigurationStruct>>(configurationName);
    };

    static std::string protocolDriverName = "protocolDriver";

    static ProtocolDriver *protocolDriverFrom(const std::shared_ptr<bootstrap::DiContainer>& dic) {
        return dic->get<ProtocolDriver *>(protocolDriverName);
    };

    static std::string autoEventManagerName = "autoEventManager";

    static std::shared_ptr<AutoEventManager> autoEventManagerFrom(const std::shared_ptr<bootstrap::DiContainer>& dic) {
        return dic->get<std::shared_ptr<AutoEventManager>>(autoEventManagerName);
    };

    static std::string messagingClientName = "messagingClient";

    static std::shared_ptr<MessagingClient> messagingClientFrom(const std::shared_ptr<bootstrap::DiContainer>& dic) {
        return dic->get<std::shared_ptr<MessagingClient>>(messagingClientName);
    };
}

#endif //PHECDA_DEVICE_SDK_CONTAINER_H
