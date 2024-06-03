//
// Created by fengxiaotx on 2024/6/3.
//

#include "phecda/util/YMLUtils.h"


namespace phecda::util {
    std::map<std::string, std::any> YMLUtils::ymoToMap(YAML::Node node) {
        std::map<std::string, std::any> map;
        if (node.IsMap()) {
            for (auto it = node.begin(); it != node.end(); it++) {
                auto key = it->first.as<std::string>();
                YAML::Node value = it->second;
                if (value.IsMap()) {
                    map[key] = ymoToMap(value);
                } else if (value.IsSequence()) {
                    map[key] = ymoToMap(value);
                } else if (value.IsScalar()) {
                    map[key] = value.as<std::string>();
                } else {
                    map[key] = value;
                }
            }
        }
        return map;
    }
} // util
// phecda