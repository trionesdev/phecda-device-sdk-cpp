//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_SDK_BOOTSTRAP_BOOTSTRAP_H
#define PHECDA_DEVICE_SDK_BOOTSTRAP_BOOTSTRAP_H

#include <functional>
#include "phecda/bootstrap/di.h"
#include "phecda/bootstrap/interfaces.h"
#include "phecda/bootstrap/flags.h"
#include "phecda/contracts/WaitGroup.h"
#include "phecda/bootstrap/startup.h"
#include "phecda/sdk/config.h"

namespace phecda::bootstrap {
    struct BootstrapHandlerArgs {
        std::shared_ptr<contracts::WaitGroup> wg;
        Container *dic;
        Timer *startupTimer;
    };

    std::shared_ptr<contracts::WaitGroup> runAndReturnWaitGroup(
            CommonArgs *args,
            std::string &serviceKey,
            sdk::ConfigurationStruct *serviceConfig,
            Timer *startupTimer,
            Container *dic,
            std::list<std::function<bool(BootstrapHandlerArgs)>> bootstrapHandlers);

}
#endif