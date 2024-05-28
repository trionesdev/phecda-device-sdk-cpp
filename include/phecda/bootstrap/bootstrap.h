//
// Created by fengxiaotx on 2024/5/22.
//
#include <functional>
#include "phecda/bootstrap/di.h"
#include "phecda/bootstrap/interfaces.h"
#include "phecda/bootstrap/flags.h"

namespace phecda::bootstrap {
    struct BootstrapHandlerArgs {
        Container *dic;
    };

    void runAndReturnWaitGroup(
            CommonArgs args,
            std::string serviceKey,
            Configuration serviceConfig,
            Container *dic,
            std::list<std::function<bool(BootstrapHandlerArgs)>> bootstrapHandlers);

}
