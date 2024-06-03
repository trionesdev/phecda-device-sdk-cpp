//
// Created by fengxiaotx on 2024/6/3.
//

#ifndef PHECDA_DEVICE_SDK_PROCESSOR_H
#define PHECDA_DEVICE_SDK_PROCESSOR_H


#include "flags.h"
#include "environement.h"
#include "startup.h"
#include "interfaces.h"
#include  <phecda/bootstrap/di.h>
#include  <phecda/sdk/config.h>


namespace phecda::bootstrap {

    class Processor {
    private:
        CommonArgs *args;
        Variables *variables;
        Timer *startupTimer;
        Container *dic;

    public:
        static Processor *newProcessor(CommonArgs *args, Variables *variables, Timer *startupTimer, Container *dic);

        void process(std::string serviceKey, sdk::ConfigurationStruct *serviceConfig);
    };

} // bootstrap
// phecda

#endif //PHECDA_DEVICE_SDK_PROCESSOR_H
