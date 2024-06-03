//
// Created by fengxiaotx on 2024/6/3.
//

#ifndef PHECDA_DEVICE_SDK_YMLUTILS_H
#define PHECDA_DEVICE_SDK_YMLUTILS_H


#include <map>
#include <string>
#include <any>
#include <yaml-cpp/yaml.h>

namespace phecda::util {

    class YMLUtils {
    public:
        static std::map<std::string, std::any> ymoToMap(YAML::Node node);
    };

} // util
// phecda

#endif //PHECDA_DEVICE_SDK_YMLUTILS_H
