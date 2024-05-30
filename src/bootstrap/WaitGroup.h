//
// Created by fengxiaotx on 2024/5/30.
//

#ifndef PHECDA_DEVICE_SDK_WAITGROUP_H
#define PHECDA_DEVICE_SDK_WAITGROUP_H
#include <iostream>
#include <mutex>

namespace phecda::contracts {

    class WaitGroup {
    private:
        int count_;
        std::mutex mtx_;
        std::condition_variable cv_;
    public:

    };

} // contracts
// phecda

#endif //PHECDA_DEVICE_SDK_WAITGROUP_H
