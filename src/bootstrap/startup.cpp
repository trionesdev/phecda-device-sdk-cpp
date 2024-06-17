//
// Created by fengxiaotx on 2024/6/3.
//

#include "phecda/bootstrap/startup.h"

namespace phecda::bootstrap {

    std::shared_ptr<Timer> Timer::newStartUpTimer(std::string serviceKey) {
        auto timer = std::make_shared<Timer>();
        return timer;
    }
}