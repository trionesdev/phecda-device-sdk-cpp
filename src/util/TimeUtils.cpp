//
// Created by fengxiaotx on 2024/6/27.
//

#include <chrono>
#include "phecda/util/TimeUtils.h"


namespace phecda::util {
        long long TimeUtils::timestamp() {
            auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
            );
            return currentTime.count();
        }
    } // util
// phecda