//
// Created by fengxiaotx on 2024/6/20.
//

#include "phecda/sdk/common_utils.h"
#include "phecda/sdk/cache.h"
#include "phecda/sdk/container.h"
#include <log4cxx/logger.h>

namespace phecda::sdk {
    static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("auto_event"));

    void
    sendEvent(contracts::Event event, const std::string &correlationID,
              const std::shared_ptr<bootstrap::DiContainer> &dic) {
        LOG4CXX_INFO(logger, "send event: event");
        sdk::container::messagingClientFrom(dic)->publish(
                event.profileName + "/" + event.deviceName + "/thing/event/post", event.toJsonString());
    };

    void addEventTags(contracts::Event event) {
        auto cmd = cache::profiles()->deviceCommand(event.profileName, event.sourceName);
        if (cmd.has_value()) {
            auto cmdTags = cmd.value().tags;
            if (!cmdTags.empty()) {
                event.tags.insert(cmdTags.begin(), cmdTags.end());
            }
        }
        auto device = cache::devices()->forName(event.deviceName);
        if (device.has_value()) {
            auto deviceTags = device.value().tags;
            if (!deviceTags.empty()) {
                event.tags.insert(deviceTags.begin(), deviceTags.end());
            }
        }
    };

    void addReadingTags(contracts::BaseReading reading) {
        auto dr = cache::profiles()->deviceResource(reading.profileName, reading.resourceName);
        if (dr.has_value()) {
            auto drTags = dr.value().tags;
            if (!drTags.empty()) {
                reading.tags.insert(drTags.begin(), drTags.end());
            }
        }
    };

} // phecda