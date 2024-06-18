//
// Created by fengxiaotx on 2024/6/17.
//

#include <regex>
#include "phecda/util/DurationUtils.h"


namespace phecda::util {
    std::chrono::duration<int> DurationUtils::parse(std::string value) {
        std::regex pattern(R"((\d+)([a-z]+))");
        std::smatch matches;
        if (std::regex_search(value, matches, pattern)) {
            int num = std::stoi(matches[1].str());
            std::string unit = matches[2].str();
            if (unit == "s") {
                return std::chrono::seconds(num);
            } else if (unit == "m") {
                return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::minutes(num));
            } else if (unit == "h") {
            }
        }
        return std::chrono::seconds(0);
    }
} // utils
// phecda