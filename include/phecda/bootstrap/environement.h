//
// Created by fengxiaotx on 2024/5/23.
//

#ifndef PHECDA_DEVICE_SDK_VARIABLES_H
#define PHECDA_DEVICE_SDK_VARIABLES_H

#include <string>
#include <list>
#include <map>
#include <any>
#include "phecda/util/SystemUtils.h"

namespace phecda::bootstrap {


    struct StartupInfo {
        int duration = 0;
        int interval = 0;
    };

    class Variables {
    private:
        static const int _bootTimeoutSecondsDefault = 60;
        static const int _bootRetrySecondsDefault = 1;
        inline static std::string _envKeyCommonConfig = "PECDA_COMMON_CONFIG";
        inline static const std::string _envKeyStartupDuration = "PHECDA_STARTUP_DURATION";
        inline static std::string _envKeyStartupInterval = "PHECDA_STARTUP_INTERVAL";
        inline static std::string _envKeyConfigDir = "PHECDA_CONFIG_DIR";
        inline static std::string _envKeyProfile = "PHECDA_PROFILE";
        inline static std::string _envKeyConfigFile = "PHECDA_CONFIG_FILE";
        std::string configPathSeparator = "/";
        std::string configNameSeparator = "-";
        std::string envNameSeparator = "_";
        std::map<std::string, std::string> _variables = {};

        static void logEnvironmentOverride(std::string name, std::string key, std::string value);

    public:
        inline static const std::list<std::string> args = {};
        inline static std::map<std::string, std::string> envVars = {};

        static Variables *newVariables();

        static StartupInfo getStartupInfo(std::string serviceKey);

        static std::string getConfigDir(std::string configDir);

        static std::string getProfileDir(std::string profileDir);

        static std::string getConfigFileName(std::string configFileName);

        static std::string getCommonConfigFileName(std::string commonConfigFileName);

        int overrideConfigMapValues(std::map<std::string, std::any> configMap);

        std::any getConfigMapValue(std::string path, std::map<std::string, std::any> configMap);

        void setConfigMapValue(std::string path, std::any value, std::map<std::string, std::any> configMap);

        std::list<std::string> buildPaths(std::map<std::string, std::any> keyMap);

        std::map<std::string, std::any> buildOverrideNames(std::list<std::string> paths);

        std::string getOverrideNameFor(std::string path);
    };
}
#endif //PHECDA_DEVICE_SDK_VARIABLES_H
