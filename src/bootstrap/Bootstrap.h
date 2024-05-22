//
// Created by fengxiaotx on 2024/5/22.
//
#include <functional>

namespace phecda {
    struct BootstrapHandlerArgs {
        Container *dic;
    };

    void runAndReturnWaitGroup(
            std::list<std::function<bool(BootstrapHandlerArgs)>> bootstrapHandlers
    ) {

    }
}