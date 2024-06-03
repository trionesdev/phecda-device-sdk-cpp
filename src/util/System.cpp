//
// Created by fengxiaotx on 2024/5/23.
//

#include "phecda/util/System.h"
#include <boost/process.hpp>

namespace phecda::util {

    std::map<std::string, std::string> System::getEnv() {
        std::map<std::string, std::string> envVars;

        // for (char **env = environ; *env != nullptr; ++env) {
        //     std::string var(*env);
        //     size_t pos = var.find('=');
        //     if (pos != std::string::npos) {
        //         std::string key = var.substr(0, pos);
        //         std::string value = var.substr(pos + 1);
        //         envVars[key] = value;
        //     }
        // }
        for (const auto &var: boost::this_process::environment()) {
            envVars[var.get_name()] = var.to_string();
        }
        return envVars;
    }

    std::string System::getEnv(const std::string& key) {
        auto env = boost::this_process::environment();
        return env[key].to_string();
    }

} // phecda