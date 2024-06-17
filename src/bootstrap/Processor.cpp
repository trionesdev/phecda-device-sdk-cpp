//
// Created by fengxiaotx on 2024/6/3.
//

#include "phecda/bootstrap/Processor.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <utility>



namespace phecda::bootstrap {
    Processor *Processor::newProcessor(CommonArgs *args, Variables *variables, std::shared_ptr<Timer> startupTimer, DiContainer *dic) {
        auto *processor = new Processor();
        processor->args = args;
        processor->variables = variables;
        processor->startupTimer = std::move(startupTimer);
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


    void loadConfigYamlFromFile(const std::string &configFile, sdk::ConfigurationStruct *serviceConfig) {
        try {
            YAML::Node config = YAML::LoadFile(configFile);
            serviceConfig->MaxEventSize = config["MaxEventSize"].as<int>();
            sdk::DeviceInfo deviceInfo{};
            auto device = config["Device"];
            if (device && !device.IsNull()) {
                auto profilesDir = device["ProfilesDir"];
                if (profilesDir && !profilesDir.IsNull()) {
                    deviceInfo.profilesDir = profilesDir.as<std::string>();
                }
                auto devicesDir = device["DevicesDir"];
                if (devicesDir && !devicesDir.IsNull()) {
                    deviceInfo.devicesDir = devicesDir.as<std::string>();
                }
            }

            serviceConfig->device = deviceInfo;

            sdk::MqttInfo mqttInfo{};
            auto mqtt = config["MQTT"];
            if (mqtt && !mqtt.IsNull()) {
                auto clientId = mqtt["ClientId"];
                if (clientId && !clientId.IsNull()) {
                    mqttInfo.clientId = clientId.as<std::string>();
                }
                auto protocol = mqtt["Protocol"];
                if (protocol && !protocol.IsNull()) {
                    mqttInfo.protocol = protocol.as<std::string>();
                }
                auto host = mqtt["Host"];
                if (host && !host.IsNull()) {
                    mqttInfo.host = host.as<std::string>();
                }
                auto port = mqtt["Port"];
                if (port && !port.IsNull()) {
                    mqttInfo.port = port.as<int>();
                }
                auto username = mqtt["Username"];
                if (username && !username.IsNull()) {
                    mqttInfo.username = username.as<std::string>();
                }
                auto password = mqtt["Password"];
                if (password && !password.IsNull()) {
                    mqttInfo.password = password.as<std::string>();
                }
                auto qos = mqtt["QOS"];
                if (qos && !qos.IsNull()) {
                    mqttInfo.qos = qos.as<int>();
                }
                auto connectionTimeout = mqtt["ConnectionTimeout"];
                if (connectionTimeout && !connectionTimeout.IsNull()) {
                    mqttInfo.connectionTimeout = connectionTimeout.as<int>();
                }
                auto keepAliveInterval = mqtt["KeepAliveInterval"];
                if (keepAliveInterval && !keepAliveInterval.IsNull()) {
                    mqttInfo.keepAliveInterval = keepAliveInterval.as<int>();
                }
                auto cleanSession = mqtt["CleanSession"];
                if (cleanSession && !cleanSession.IsNull()) {
                    mqttInfo.cleanSession = cleanSession.as<bool>();
                }
                auto automaticReconnect = mqtt["AutomaticReconnect"];
                if (automaticReconnect && !automaticReconnect.IsNull()) {
                    mqttInfo.automaticReconnect = automaticReconnect.as<bool>();
                }
                auto topicPrefix = mqtt["TopicPrefix"];
                if (topicPrefix && !topicPrefix.IsNull()) {
                    mqttInfo.topicPrefix = topicPrefix.as<std::string>();
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