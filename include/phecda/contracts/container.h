//
// Created by fengxiaotx on 2024/5/28.
//

#ifndef PHECDA_DEVICE_SDK_CONTRACTS_CONTAINER_H
#define PHECDA_DEVICE_SDK_CONTRACTS_CONTAINER_H

#include <string>
#include <phecda/contracts/model.h>
#include "phecda/bootstrap/di-container.h"

namespace phecda::contracts::container {
    static std::string deviceServiceName = "deviceServiceName";

    DeviceService *deviceServiceFrom(bootstrap::DiContainer *dic);
}

#endif //PHECDA_DEVICE_SDK_CONTRACTS_CONTAINER_H
