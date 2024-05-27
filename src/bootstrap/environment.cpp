//
// Created by fengxiaotx on 2024/5/27.
//
#include "environement.h"

namespace phecda::bootstrap {
    Variables Variables::newVariables() {
        Variables variables;
        return variables;
    }

    void Variables::logEnvironmentOverride(std::string name, std::string key, std::string value) {

    }

    StartupInfo Variables::getStartupInfo(std::string serviceKey) {
        StartupInfo startupInfo{
                .duration = bootTimeoutSecondsDefault,
                .interval = bootRetrySecondsDefault,
        };
        auto durationValue = util::System::getEnv(envKeyStartupDuration);
        if (!durationValue.empty()) {
            logEnvironmentOverride("Startup Duration", envKeyStartupDuration, durationValue);
            startupInfo.duration = std::stoi(durationValue);
        }
        auto intervalValue = util::System::getEnv(envKeyStartupInterval);
        if (!intervalValue.empty()) {
            logEnvironmentOverride("Startup Interval", envKeyStartupInterval, intervalValue);
            startupInfo.interval = std::stoi(intervalValue);
        }
        return startupInfo;
    }

    std::string Variables::getConfigDir(std::string configDir) {
        return std::string();
    }

    std::string Variables::getProfileDir(std::string profileDir) {
        return std::string();
    }

    std::string Variables::getConfigFileName(std::string configFileName) {
        return std::string();
    }

    std::string Variables::getCommonConfigFileName(std::string commonConfigFileName) {
        return std::string();
    }

    int Variables::overrideConfigMapValues(std::map<std::string, std::any> configMap) {
        return 0;
    }

    std::any Variables::getConfigMapValue(std::string path, std::map<std::string, std::any> configMap) {
        return std::any();
    }

    void Variables::setConfigMapValue(std::string path, std::any value, std::map<std::string, std::any> configMap) {

    }

    std::list<std::string> Variables::buildPaths(std::map<std::string, std::any> keyMap) {
        return std::list<std::string>();
    }

    std::map<std::string, std::any> Variables::buildOverrideNames(std::list<std::string> paths) {
        return std::map<std::string, std::any>();
    }

    std::string Variables::getOverrideNameFor(std::string path) {
        return std::string();
    }
}