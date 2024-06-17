//
// Created by fengxiaotx on 2024/5/27.
//
#include <phecda/bootstrap/bootstrap.h>
#include "phecda/bootstrap/Processor.h"
#include "phecda/sdk/container.h"


namespace phecda::bootstrap {

    std::shared_ptr<contracts::WaitGroup> runAndReturnWaitGroup(
            CommonArgs *args_,
            std::string &serviceKey,
            sdk::ConfigurationStruct *serviceConfig,
            std::shared_ptr<Timer> startupTimer,
            DiContainer *dic,
            std::list<std::function<bool(BootstrapHandlerArgs)>> bootstrapHandlers) {
        std::shared_ptr<contracts::WaitGroup> wg = std::make_unique<contracts::WaitGroup>();
        auto envVars_ = Variables::newVariables();
        auto processor = Processor::newProcessor(args_, envVars_, startupTimer, dic);
        processor->process(serviceKey, serviceConfig);
        dic->update({
                            {sdk::container::configurationName, serviceConfig},
                    });
        if (bootstrapHandlers.empty()) {
            return wg;
        }
        for (const auto &handler: bootstrapHandlers) {
            BootstrapHandlerArgs handlerArgs;
            handlerArgs.wg = wg;
            handlerArgs.dic = dic;
            handlerArgs.startupTimer = startupTimer;
            if (!handler(handlerArgs)) {
                break;
            }
        }
        return wg;
    }

}