//
// Created by fengxiaotx on 2024/6/3.
//
#include "phecda/bootstrap/startup.h"
namespace phecda::bootstrap{

    Timer* Timer::newStartUpTimer(std::string serviceKey) {
        auto *timer = new Timer();

        return timer;
    }
}