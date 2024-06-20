//
// Created by fengxiaotx on 2024/6/17.
//

#ifndef PHECDA_DEVICE_SDK_APPLICATION_H
#define PHECDA_DEVICE_SDK_APPLICATION_H

#include <optional>
#include <phecda/contracts/model.h>
#include "phecda/bootstrap/di-container.h"

namespace phecda::sdk::application {

    std::optional<contracts::Event> getCommand(
            const std::string &deviceName, const std::string &commandName, const std::string &queryParams,
            bool regexCmd,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    );

    std::optional<contracts::Event> setCommand(
            const std::string &deviceName, const std::string &commandName, const std::string &queryParams,
            const std::map<std::string, std::any> &requests,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    );

} // sdk
// phecda

#endif //PHECDA_DEVICE_SDK_APPLICATION_H
