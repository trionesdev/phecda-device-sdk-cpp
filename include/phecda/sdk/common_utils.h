//
// Created by fengxiaotx on 2024/6/20.
//

#ifndef PHECDA_DEVICE_SDK_COMMON_UTILS_H
#define PHECDA_DEVICE_SDK_COMMON_UTILS_H

#include <memory>
#include <phecda/contracts/model.h>
#include <phecda/bootstrap/di_container.h>

namespace phecda::sdk {

    void sendEvent(const contracts::Event& event, const std::string &correlationID,
                   const std::shared_ptr<bootstrap::DiContainer> &dic);

    void addEventTags(contracts::Event event);

    void addReadingTags(contracts::BaseReading);

} // phecda

#endif //PHECDA_DEVICE_SDK_COMMON_UTILS_H
