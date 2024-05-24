//
// Created by fengxiaotx on 2024/5/22.
//
#include <functional>

#include "phecda/bootstrap/di.h"

namespace phecda::bootstrap {
    struct BootstrapHandlerArgs {
        Container *dic;
    };

    void runAndReturnWaitGroup(
            std::list<std::function<bool(BootstrapHandlerArgs)>> bootstrapHandlers
    ) {

    }
}
