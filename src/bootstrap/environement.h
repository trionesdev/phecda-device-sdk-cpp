//
// Created by fengxiaotx on 2024/5/23.
//

#ifndef PHECDA_DEVICE_SDK_VARIABLES_H
#define PHECDA_DEVICE_SDK_VARIABLES_H

#include <string>
#include <list>
#include <map>
#include <any>
#include "../util/System.h"

namespace phecda::bootstrap {
    static const std::list<std::string> args = {};
    static std::map<std::string, std::string> envVars = {};

    struct StartupInfo {
        int duration = 0;
        int interval = 0;
    };

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
        std::map<std::string, std::string> _variables = {};

        void logEnvironmentOverride(std::string name, std::string key, std::string value);

    public:
        static Variables newVariables();

        StartupInfo getStartupInfo(std::string serviceKey);

        std::string getConfigDir(std::string configDir);

        std::string getProfileDir(std::string profileDir);

        std::string getConfigFileName(std::string configFileName);

        std::string getCommonConfigFileName(std::string commonConfigFileName);

        int overrideConfigMapValues(std::map<std::string, std::any> configMap);

        std::any getConfigMapValue(std::string path, std::map<std::string, std::any> configMap);

        void setConfigMapValue(std::string path, std::any value, std::map<std::string, std::any> configMap);

        std::list<std::string> buildPaths(std::map<std::string, std::any> keyMap);

        std::map<std::string, std::any> buildOverrideNames(std::list<std::string> paths);

        std::string getOverrideNameFor(std::string path);
    };
}
#endif //PHECDA_DEVICE_SDK_VARIABLES_H
