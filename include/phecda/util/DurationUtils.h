//
// Created by fengxiaotx on 2024/6/17.
//

#ifndef PHECDA_DEVICE_SDK_DURATIONUTILS_H
#define PHECDA_DEVICE_SDK_DURATIONUTILS_H


#include <chrono>
#include <iostream>
#include <string>

namespace phecda::util {

        class DurationUtils {
        public:
           static std::chrono::duration<int> parse(std::string value);
        };

    } // utils
// phecda

#endif //PHECDA_DEVICE_SDK_DURATIONUTILS_H
