//
// Created by fengxiaotx on 2024/6/18.
//

#ifndef PHECDA_DEVICE_SDK_TIMER_H
#define PHECDA_DEVICE_SDK_TIMER_H

#include <functional>
#include <thread>

namespace phecda::util {

    class Timer {
    private:
        bool running_;
        std::thread thread_;
    public:
        Timer() : running_(false) {}
        void schedule(std::function<void()> &run, long long delay, long long period);

        void stop();
    };


} // Timer

#endif //PHECDA_DEVICE_SDK_TIMER_H
