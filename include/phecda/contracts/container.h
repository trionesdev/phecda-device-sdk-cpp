//
// Created by fengxiaotx on 2024/5/28.
//

#ifndef PHECDA_DEVICE_SDK_CONTRACTS_CONTAINER_H
#define PHECDA_DEVICE_SDK_CONTRACTS_CONTAINER_H

#include <string>
#include <phecda/contracts/model.h>
#include "phecda/bootstrap/di_container.h"

namespace phecda::contracts::container {
    static std::string deviceServiceName = "deviceServiceName";


    static std::shared_ptr<DeviceService> deviceServiceFrom(const std::shared_ptr<bootstrap::DiContainer> &dic) {
        return dic->get<std::shared_ptr<DeviceService> >(deviceServiceName);
    }

}

#endif //PHECDA_DEVICE_SDK_CONTRACTS_CONTAINER_H
