//
// Created by fengxiaotx on 2024/6/4.
//
#include "phecda/sdk/provision.h"
#include <phecda/contracts/container.h>
#include <phecda/sdk/cache.h>
#include <filesystem>
#include <iostream>
#include <yaml-cpp/yaml.h>

namespace fs = std::filesystem;

namespace phecda::sdk::provision {

    FileType getFileType(const fs::path& filePath) {
        std::string extension = filePath.extension().string();
        if (extension == ".json") {
            return FileType::JSON;
        } else if (extension == ".yaml" || extension == ".yml") {
            return FileType::YAML;
        } else {
            return FileType::OTHER;
        }
    }

    contracts::DeviceProfile deviceProfileFromYamlFile(const fs::path &path) {
        auto deviceProfile = contracts::DeviceProfile();
        YAML::Node config = YAML::LoadFile(path.string());
        auto name = config["name"];
        if (name.IsDefined()) {
            deviceProfile.name = name.as<std::string>();
        }
        auto manufacturer = config["manufacturer"];
        if (manufacturer.IsDefined()) {
            deviceProfile.manufacturer = manufacturer.as<std::string>();
        }
        auto model = config["model"];
        if (model.IsDefined()) {
            deviceProfile.model = model.as<std::string>();
        }
        auto labels = config["labels"];
        if (labels.IsDefined()) {
            for (auto label: labels) {
                deviceProfile.labels.push_back(label.as<std::string>());
            }
        }
        auto description = config["description"];
        if (description.IsDefined()) {
            deviceProfile.description = description.as<std::string>();
        }
        auto deviceResources = config["deviceResources"];
        if (deviceResources.IsDefined()) {
            for (auto deviceResource: deviceResources) {
                auto deviceResourceStruct = contracts::DeviceResource();
                auto resourceName = deviceResource["name"];
                if (resourceName.IsDefined()) {
                    deviceResourceStruct.name = resourceName.as<std::string>();
                }
                auto resDescription = deviceResource["description"];
                if (resDescription.IsDefined()) {
                    deviceResourceStruct.description = resDescription.as<std::string>();
                }
                auto resProperties = deviceResource["properties"];
                if (resProperties.IsDefined()) {
                    auto resourceProperties = contracts::ResourceProperties();
                    auto valueType = resProperties["valueType"];
                    if (valueType.IsDefined()) {
                        resourceProperties.valueType = valueType.as<std::string>();
                    }
                    auto readWrite = resProperties["readWrite"];
                    if (readWrite.IsDefined()) {
                        resourceProperties.readWrite = readWrite.as<std::string>();
                    }
                    auto mediaType = resProperties["mediaType"];
                    if (mediaType.IsDefined()) {
                        resourceProperties.mediaType = mediaType.as<std::string>();
                    }
                    deviceResourceStruct.properties = resourceProperties;
                }
                deviceProfile.deviceResources.push_back(deviceResourceStruct);
            }
        }
        return deviceProfile;
    }

    contracts::DeviceProfile processProfiles(const fs::path &path) {
        auto fileType = getFileType(path);
        switch (fileType) {
            case FileType::JSON:
                return {};
            case FileType::YAML:
                return deviceProfileFromYamlFile(path);
            default:
                return {};
        }
    }

    std::list<contracts::DeviceProfile> loadProfilesFromFile(const std::string &path) {
        std::filesystem::path configFilePath = std::filesystem::path(path);
        std::list<contracts::DeviceProfile> profiles = {};
        for (const auto &entry: fs::directory_iterator(configFilePath)) {
            if (fs::is_regular_file(entry)) {
                auto profile = processProfiles(entry);
                profiles.push_back(profile);
            }
        }
        return profiles;
    }

    void loadProfiles(const std::string &path, phecda::bootstrap::DiContainer *container) {
        if (path.empty()) {
            return;
        }
        auto profiles = loadProfilesFromFile(path);
        for (const auto &profile: profiles) {
            phecda::sdk::cache::profiles()->add(profile);
        }
    };

    std::list<contracts::Device> deviceFromYamlFile(const fs::path &path) {
        auto deviceProfile = contracts::DeviceProfile();
        std::list<contracts::Device> devices = {};
        YAML::Node config = YAML::LoadFile(path.string());
        auto deviceList = config["deviceList"];
        if (deviceList.IsDefined() && deviceList.IsSequence()) {
            for (auto device: deviceList) {
                auto deviceStruct = contracts::Device();

                auto name = device["name"];
                if (name.IsDefined() && !name.IsNull()) {
                    deviceStruct.name = name.as<std::string>();
                }
                auto profileName = device["profileName"];
                if (profileName.IsDefined() && !profileName.IsNull()) {
                    deviceStruct.profileName = profileName.as<std::string>();
                }
                auto description = device["description"];
                if (description.IsDefined() && !description.IsNull()) {
                    deviceStruct.description = description.as<std::string>();
                }
                auto labels = device["labels"];
                if (labels.IsDefined() && labels.IsSequence()) {
                    for (auto label: labels) {
                        deviceStruct.labels.push_back(label.as<std::string>());
                    }
                }
                auto tags = device["tags"];
                if (tags.IsDefined() && tags.IsMap()) {
                    for (auto tag: tags) {
                        deviceStruct.tags.insert({tag.first.as<std::string>(), tag.second.as<std::string>()});
                    }
                }
                auto protocols = device["protocols"];
                if (protocols.IsDefined() && protocols.IsMap()) {
                    for (auto protocol: protocols) {
                        if (protocol.second.IsMap()) {
                            std::map<std::string, std::any> protocolValue = {};
                            for (auto value: protocol.second) {
                                protocolValue.insert({value.first.as<std::string>(), value.second.as<std::string>()});
                            }
                            deviceStruct.protocols.insert({protocol.first.as<std::string>(), protocolValue});
                        }
                    }
                }
                auto autoEvents = device["autoEvents"];
                if (autoEvents.IsDefined() && autoEvents.IsSequence()) {
                    for (auto autoEvent: autoEvents) {
                        auto autoEventStruct = contracts::AutoEvent();
                        auto interval = autoEvent["interval"];
                        if (interval.IsDefined() && !interval.IsNull()) {
                            autoEventStruct.interval = interval.as<std::string>();
                        }
                        auto onChange = autoEvent["onChange"];
                        if (onChange.IsDefined() && !onChange.IsNull()) {
                            autoEventStruct.onChange = onChange.as<bool>();
                        }
                        auto sourceName = autoEvent["sourceName"];
                        if (sourceName.IsDefined() && !sourceName.IsNull()) {
                            autoEventStruct.sourceName = sourceName.as<std::string>();
                        }
                        deviceStruct.autoEvents.push_back(autoEventStruct);
                    }
                }
                devices.push_back(deviceStruct);
            }
        }
        return devices;
    }

    std::list<contracts::Device> processDevices(const fs::path &path) {
        auto fileType = getFileType(path);
        switch (fileType) {
            case FileType::JSON:
                return {};
            case FileType::YAML:
                return deviceFromYamlFile(path);
            default:
                return {};
        }
    }

    std::list<contracts::Device> loadDevicesFromFile(const std::string &path, std::string serviceName) {
        std::filesystem::path configFilePath = std::filesystem::path(path);
        std::list<contracts::Device> devices = {};
        for (const auto &entry: fs::directory_iterator(configFilePath)) {
            if (fs::is_regular_file(entry)) {
                auto filesDevices = processDevices(entry);
                devices.insert(devices.end(), filesDevices.begin(), filesDevices.end());
            }
        }
        return devices;
    }

    void loadDevices(const std::string &path, phecda::bootstrap::DiContainer *dic) {
        if (path.empty()) {
            return;
        }
        auto serviceName = contracts::container::deviceServiceFrom(dic)->name;
        auto devices = loadDevicesFromFile(path, serviceName);
        for (const auto &device: devices) {
            phecda::sdk::cache::devices()->add(device);
        }
    }
}