//
// Created by fengxiaotx on 2024/6/20.
//

#ifndef PHECDA_DEVICE_SDK_COMMON_UTILS_H
#define PHECDA_DEVICE_SDK_COMMON_UTILS_H

#include <memory>
#include <phecda/contracts/model.h>
#include <phecda/bootstrap/di-container.h>

namespace phecda::sdk {

    void sendEvent(contracts::Event event, std::string correlationID, std::shared_ptr<bootstrap::DiContainer> dic);

    void addEventTags(contracts::Event event);

    void addReadingTags(contracts::BaseReading);

} // phecda

#endif //PHECDA_DEVICE_SDK_COMMON_UTILS_H
