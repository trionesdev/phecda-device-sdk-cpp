//
// Created by fengxiaotx on 2024/5/28.
//

#ifndef PHECDA_DEVICE_SDK_STARTUP_H
#define PHECDA_DEVICE_SDK_STARTUP_H

#include <string>
#include <memory>
#include <chrono>

namespace phecda::bootstrap {
    class Timer {
    public:
        std::chrono::system_clock::time_point startTime;
        std::chrono::seconds duration;
        std::chrono::seconds interval;

        static std::shared_ptr<Timer> newStartUpTimer(const std::string &serviceKey);

        std::string sinceAsString();

        bool hasNotElapsed();

        void sleepForInterval();
    };
}
#endif //PHECDA_DEVICE_SDK_STARTUP_H
