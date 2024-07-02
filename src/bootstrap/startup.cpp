//
// Created by fengxiaotx on 2024/6/3.
//

#include <thread>
#include "phecda/bootstrap/startup.h"
#include "phecda/bootstrap/environement.h"

namespace phecda::bootstrap {

    std::shared_ptr<Timer> Timer::newStartUpTimer(const std::string &serviceKey) {
        auto startup = Variables::getStartupInfo(serviceKey);
        auto timer = std::make_shared<Timer>();
        timer->startTime = std::chrono::system_clock::now();
        timer->duration = std::chrono::seconds(startup.duration);
        timer->interval = std::chrono::seconds(startup.interval);
        return timer;
    }

    std::string Timer::sinceAsString() {
        return std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - startTime).count()) + "s";
    }

    bool Timer::hasNotElapsed() {
        return (std::chrono::system_clock::now() - (startTime + duration)) < std::chrono::seconds(0);
    }

    void Timer::sleepForInterval() {
        std::this_thread::sleep_for(interval);
    }
}