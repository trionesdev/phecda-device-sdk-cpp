//
// Created by fengxiaotx on 2024/7/1.
//

#include "phecda/sdk/messaging.h"
#include <phecda/sdk/container.h>
#include <phecda/sdk/mqtt.h>
#include <phecda/log/log.h>

namespace phecda::sdk {
    static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sdk/messaging"));

    std::shared_ptr<MessagingClient>
    newMessagingClient(const std::shared_ptr<ConfigurationStruct> &configuration,
                       const std::shared_ptr<DiContainer> &dic) {
        return MqttMessagingClient::newMqttClient(configuration->mqtt, dic);
    }

    bool messagingBootstrapHandler(const bootstrap::BootstrapHandlerArgs &args) {
        auto configuration = sdk::container::configurationFrom(args.dic);
        std::shared_ptr<MessagingClient> messagingClient;
        try {
            messagingClient = newMessagingClient(configuration, args.dic);
        } catch (std::exception &e) {
            LOG_ERROR(logger, "Failed to create ChannelClient:" << e.what());
            return false;
        }
        args.dic->update({{container::messagingClientName, messagingClient}});
        while (args.startupTimer->hasNotElapsed()) {
            try {
                messagingClient->connect();
            } catch (std::exception &e) {
                LOG_WARN(logger, "Failed to connect to server:" << e.what());
                args.startupTimer->sleepForInterval();
                continue;
            }
            args.dic->update({{container::messagingClientName, messagingClient}});
            return true;
        }
        LOG_ERROR(logger, "Connecting to ChannelClient timeout");
        return true;
    };
} // sdk
// phecda