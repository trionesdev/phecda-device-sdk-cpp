//
// Created by fengxiaotx on 2024/6/3.
//

#ifndef PHECDA_DEVICE_SDK_PROCESSOR_H
#define PHECDA_DEVICE_SDK_PROCESSOR_H

#include <iostream>
#include <phecda/bootstrap/flags.h>
#include "environement.h"
#include "startup.h"
#include "interfaces.h"
#include  <phecda/bootstrap/di-container.h>
#include  <phecda/sdk/config.h>


namespace phecda::bootstrap {

    class Processor {
    private:
        CommonArgs *args;
        Variables *variables;
        std::shared_ptr<Timer> startupTimer;
        std::shared_ptr<DiContainer> dic;

    public:
        static std::shared_ptr<Processor> newProcessor(CommonArgs *args, Variables *variables, std::shared_ptr<Timer> startupTimer,
                                       std::shared_ptr<DiContainer> dic);

        void process(const std::string& serviceKey, std::shared_ptr<sdk::ConfigurationStruct> serviceConfig);
    };

} // bootstrap
// phecda

#endif //PHECDA_DEVICE_SDK_PROCESSOR_H
