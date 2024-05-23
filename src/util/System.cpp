//
// Created by fengxiaotx on 2024/5/23.
//

#include "System.h"

namespace phecda {

    std::map<std::string, std::string> System::getEnv() {
        std::map<std::string, std::string> envVars;

        // 使用 std::getenv 获取所有环境变量
        for (char **env = environ; *env != nullptr; ++env) {
            std::string var(*env);
            size_t pos = var.find('=');
            if (pos != std::string::npos) {
                std::string key = var.substr(0, pos);
                std::string value = var.substr(pos + 1);
                envVars[key] = value;
            }
        }
        return envVars;
    }

} // phecda