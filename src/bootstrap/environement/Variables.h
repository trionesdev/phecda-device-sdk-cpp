//
// Created by fengxiaotx on 2024/5/23.
//

#ifndef PHECDA_DEVICE_SDK_VARIABLES_H
#define PHECDA_DEVICE_SDK_VARIABLES_H

#include <string>
#include <list>
#include <map>
#include "../../util/System.h"

namespace phecda {
    static const std::list<std::string> args = {};
    static const std::map<std::string, std::string> envVars = {};

    class Variables {
    private:
        int bootTimeoutSecondsDefault = 60;
        int bootRetrySecondsDefault = 1;
        std::string envKeyCommonConfig = "PECDA_COMMON_CONFIG";
        std::string envKeyStartupDuration = "PHECDA_STARTUP_DURATION";
        std::string envKeyStartupInterval = "PHECDA_STARTUP_INTERVAL";
        std::string envKeyConfigDir = "PHECDA_CONFIG_DIR";
        std::string envKeyProfile = "PHECDA_PROFILE";
        std::string envKeyConfigFile = "PHECDA_CONFIG_FILE";
        std::string configPathSeparator = "/";
        std::string configNameSeparator = "-";
        std::string envNameSeparator = "_";
        std::map<std::string, std::string> envVariables = {};
    public:
        static Variables newVariables() {
            Variables variablesObj;
            variablesObj.envVariables = System::getEnv();
            return variablesObj;
        }

    };
}
#endif //PHECDA_DEVICE_SDK_VARIABLES_H
