//
// Created by fengxiaotx on 2024/5/30.
//

#include "phecda/contracts/WaitGroup.h"

namespace phecda::contracts {
    WaitGroup::WaitGroup() {
        this->count_ = 1;
    }

    void WaitGroup::add(int delta) {
        std::lock_guard<std::mutex> lock(mutex_);
        count_ += delta;
    }

    void WaitGroup::done() {
        std::lock_guard<std::mutex> lock(mutex_);
        count_--;
        if (count_ == 0) {
            condition_.notify_all();
        }
    }

    void WaitGroup::wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return count_ == 0; });
    }

    WaitGroup::~WaitGroup() = default;


} // contracts
// phecda