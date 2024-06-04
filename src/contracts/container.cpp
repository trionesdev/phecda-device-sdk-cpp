//
// Created by fengxiaotx on 2024/6/4.
//
#include <phecda/contracts/container.h>

namespace phecda::contracts::container {
    DeviceService *deviceServiceFrom(bootstrap::DiContainer *dic) {
        return dic->get<DeviceService *>(deviceServiceName);
    }
}