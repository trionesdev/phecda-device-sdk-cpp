//
// Created by fengxiaotx on 2024/6/3.
//

#include "phecda/bootstrap/Processor.h"
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include <iostream>


namespace phecda::bootstrap {
    Processor *Processor::newProcessor(CommonArgs *args, Variables *variables, Timer *startupTimer, Container *dic) {
        auto *processor = new Processor();
        processor->args = args;
        processor->variables = variables;
        processor->startupTimer = startupTimer;
        processor->dic = dic;
        return processor;
    }

    std::string getConfigFileLocation(CommonArgs *args_) {
        std::string configFileName = Variables::getConfigFileName(args_->configFileName());
        std::string configDir = Variables::getConfigDir(args_->configDirectory());
        std::string profileDir = Variables::getProfileDir(args_->profile());
        std::filesystem::path configFilePath = std::filesystem::path(configDir) / profileDir / configFileName;
        return configFilePath.string();
    }


    void loadConfigYamlFromFile(std::string configFile, sdk::ConfigurationStruct *serviceConfig) {
        try {
            YAML::Node config = YAML::LoadFile(configFile);
            serviceConfig->MaxEventSize = config["MaxEventSize"].as<int>();
            sdk::DeviceInfo deviceInfo{};
            if (!config["Device"].IsNull()) {
                auto device = config["Device"];
                if (!device["ProfilesDir"].IsNull()) {
                    deviceInfo.profilesDir = device["ProfilesDir"].as<std::string>();
                }
                if (!device["DevicesDir"].IsNull()) {
                    deviceInfo.devicesDir = device["DevicesDir"].as<std::string>();
                }
            }

            serviceConfig->device = deviceInfo;

            sdk::MqttInfo mqttInfo{};
            if (!config["MQTT"].IsNull()) {
                auto mqtt = config["MQTT"];
                if (!mqtt["Host"].IsNull()) {
                    mqttInfo.host = mqtt["Host"].as<std::string>();
                }
            }
            serviceConfig->mqtt = mqttInfo;

        } catch (YAML::Exception &e) {
            std::cout << "load config file error: " << e.what() << std::endl;
        }

    }

    void Processor::process(std::string serviceKey, sdk::ConfigurationStruct *serviceConfig) {
        std::string filePath = getConfigFileLocation(args);
        loadConfigYamlFromFile(filePath, serviceConfig);
    }
} // bootstrap
// phecda