//
// Created by fengxiaotx on 2024/5/27.
//
#include "phecda/bootstrap/environement.h"

namespace phecda::bootstrap {
    Variables *Variables::newVariables() {
        auto *variables = new Variables();
        return variables;
    }

    void Variables::logEnvironmentOverride(std::string name, std::string key, std::string value) {

    }

    StartupInfo Variables::getStartupInfo(std::string serviceKey) {
        StartupInfo startupInfo{};
        startupInfo.duration = bootTimeoutSecondsDefault;
        startupInfo.interval = bootRetrySecondsDefault;
        auto durationValue = util::SystemUtils::getEnv(envKeyStartupDuration);
        if (!durationValue.empty()) {
            logEnvironmentOverride("Startup Duration", envKeyStartupDuration, durationValue);
            startupInfo.duration = std::stoi(durationValue);
        }
        auto intervalValue = util::SystemUtils::getEnv(envKeyStartupInterval);
        if (!intervalValue.empty()) {
            logEnvironmentOverride("Startup Interval", envKeyStartupInterval, intervalValue);
            startupInfo.interval = std::stoi(intervalValue);
        }
        return startupInfo;
    }

    std::string Variables::getConfigDir(std::string configDir) {
        auto envValue = util::SystemUtils::getEnv(envKeyConfigDir);
        if (!envValue.empty()) {
            configDir = envValue;
            logEnvironmentOverride("-cf/--configDir", envKeyConfigDir, envValue);

        }
        return configDir;
    }

    std::string Variables::getProfileDir(std::string profileDir) {
        auto envValue = util::SystemUtils::getEnv(envKeyProfile);
        if (!envValue.empty()) {
            profileDir = envValue;
            logEnvironmentOverride("-pf/--profileDir", envKeyProfile, envValue);
        }
        return profileDir;
    }

    std::string Variables::getConfigFileName(std::string configFileName) {
        auto envValue = util::SystemUtils::getEnv(envKeyConfigFile);
        if (!envValue.empty()) {
            configFileName = envValue;
            logEnvironmentOverride("-cf/--configDir", envKeyConfigFile, envValue);
        }
        return configFileName;
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