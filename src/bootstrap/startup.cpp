//
// Created by fengxiaotx on 2024/6/3.
//
#include <string>
#include "phecda/bootstrap/startup.h"
namespace phecda::bootstrap{

    Timer* Timer::newStartUpTimer(std::string serviceKey) {
        Timer timer;

        return &timer;
    }
}