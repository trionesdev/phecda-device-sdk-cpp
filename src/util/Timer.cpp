//
// Created by fengxiaotx on 2024/6/18.
//

#include "phecda/util/Timer.h"

namespace phecda::util {
    void Timer::schedule(std::function<void()> &run, long long delay, long long period) {
        thread_ = std::thread([this, run, delay, period]() {
            if (delay > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
            while (running_) {
                run();
                if (period > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(period));
                }
            }
        });

    }


    void Timer::stop() {
        running_ = false;
    }


} // Timer