//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_SDK_BOOTSTRAP_BOOTSTRAP_H
#define PHECDA_DEVICE_SDK_BOOTSTRAP_BOOTSTRAP_H

#include <functional>
#include "phecda/contracts/WaitGroup.h"
#include "startup.h"
#include "flags.h"
#include "phecda/sdk/config.h"
#include "phecda/bootstrap/di-container.h"


namespace phecda::bootstrap {
    struct BootstrapHandlerArgs {
        std::shared_ptr<contracts::WaitGroup> wg;
        DiContainer *dic;
        Timer *startupTimer;
    };

    std::shared_ptr<contracts::WaitGroup> runAndReturnWaitGroup(
            CommonArgs *args,
            std::string &serviceKey,
            sdk::ConfigurationStruct *serviceConfig,
            Timer *startupTimer,
            DiContainer *dic,
            std::list<std::function<bool(BootstrapHandlerArgs)>> bootstrapHandlers);

}
#endif