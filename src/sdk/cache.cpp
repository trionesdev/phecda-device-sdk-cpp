//
// Created by fengxiaotx on 2024/6/4.
//
#include <phecda/sdk/cache.h>

namespace phecda::sdk::cache {

    std::shared_ptr<DeviceCache> DeviceCache::newDeviceCache(const std::list<contracts::Device> &devices) {
        std::map<std::string, contracts::Device> deviceMap;
        for (auto &device: devices) {
            if (!device.name.empty()) {
                deviceMap[device.name] = device;
            }
        }
        dc = std::make_shared<DeviceCache>();
        dc->deviceMap = deviceMap;
        return dc;
    }

    std::optional<contracts::Device> DeviceCache::forName(const std::string &name) {
        if (this->deviceMap.find(name) != this->deviceMap.end()) {
            return this->deviceMap[name];
        } else {
            return std::nullopt;
        }
    }

    std::list<contracts::Device> DeviceCache::all() {
        std::list<contracts::Device> devices;
        for (auto &device: this->deviceMap) {
            devices.push_back(device.second);
        }
        return devices;
    }

    void DeviceCache::add(const contracts::Device &device) {
        if (!device.name.empty()) {
            deviceMap[device.name] = device;
        }
    }

    void DeviceCache::update(const contracts::Device &device) {
        if (!device.name.empty()) {
            deviceMap[device.name] = device;
        }
    }

    void DeviceCache::removeByName(const std::string &name) {
        deviceMap.erase(name);
    }


    std::shared_ptr<ProfileCache> ProfileCache::newProfileCache(const std::list<contracts::DeviceProfile> &profiles) {
        std::map<std::string, contracts::DeviceProfile> deviceProfileMap;
        std::map<std::string, std::map<std::string, contracts::DeviceProperty>> devicePropertyMap = {};
        std::map<std::string, std::map<std::string, contracts::DeviceCommand>> deviceCommandMap = {};
        std::map<std::string, std::map<std::string, contracts::DeviceEvent>> deviceEventMap = {};
        for (auto &profile: profiles) {
            if (!profile.productKey.empty()) {
                deviceProfileMap[profile.productKey] = profile;
                std::map<std::string, contracts::DeviceProperty> profileDevicePropertyMap = {};
                for (auto &deviceProperty: profile.deviceProperties) {
                    profileDevicePropertyMap[deviceProperty.identifier] = deviceProperty;
                }
                devicePropertyMap[profile.productKey] = profileDevicePropertyMap;
                std::map<std::string, contracts::DeviceCommand> profileDeviceCommandsMap = {};
                for (auto &deviceCommand: profile.deviceCommands) {
                    profileDeviceCommandsMap[deviceCommand.identifier] = deviceCommand;
                }
                deviceCommandMap[profile.productKey] = profileDeviceCommandsMap;
                std::map<std::string, contracts::DeviceEvent> profileDeviceEventsMap = {};
                for (auto &deviceEvent: profile.deviceEvents) {
                    profileDeviceEventsMap[deviceEvent.identifier] = deviceEvent;
                }
                deviceEventMap[profile.productKey] = profileDeviceEventsMap;
            }
        }
        pc = std::make_shared<ProfileCache>();
        pc->deviceProfileMap = deviceProfileMap;
        pc->deviceProfileMap = deviceProfileMap;
        pc->deviceCommandMap = deviceCommandMap;
        pc->deviceEventMap = deviceEventMap;
        return pc;
    }

    std::optional<contracts::DeviceProfile> ProfileCache::forProductKey(const std::string &productKey) {
        if (deviceProfileMap.find(productKey) != deviceProfileMap.end()) {
            return deviceProfileMap[productKey];
        } else {
            return std::nullopt;
        }
    }

    std::list<contracts::DeviceProfile> ProfileCache::all() {
        std::list<contracts::DeviceProfile> profiles;
        if (!deviceProfileMap.empty()) {
            for (auto &profile: deviceProfileMap) {
                profiles.push_back(profile.second);
            }
        }
        return profiles;
    }

    void ProfileCache::add(const contracts::DeviceProfile &profile) {
        auto profileKey = profile.productKey;
        if (!profileKey.empty()) {
            deviceProfileMap[profileKey] = profile;
            std::map<std::string, contracts::DeviceProperty> profileDevicePropertyMap = {};
            for (auto &deviceProperty: profile.deviceProperties) {
                profileDevicePropertyMap[deviceProperty.identifier] = deviceProperty;
            }
            devicePropertyMap[profileKey] = profileDevicePropertyMap;
            std::map<std::string, contracts::DeviceCommand> profileDeviceCommandsMap = {};
            for (auto &deviceCommand: profile.deviceCommands) {
                profileDeviceCommandsMap[deviceCommand.name] = deviceCommand;
            }
            deviceCommandMap[profileKey] = profileDeviceCommandsMap;
            std::map<std::string, contracts::DeviceEvent> profileDeviceEventsMap = {};
            for (auto &deviceEvent: profile.deviceEvents) {
                profileDeviceEventsMap[deviceEvent.name] = deviceEvent;
            }
            deviceEventMap[profileKey] = profileDeviceEventsMap;
        }
    }

    void ProfileCache::update(const contracts::DeviceProfile &profile) {
        removeByProductKey(profile.productKey);
        add(profile);
    }

    void ProfileCache::removeByProductKey(const std::string &productKey) {
        auto it = deviceProfileMap.find(productKey);
        if (it != deviceProfileMap.end()) {
            deviceProfileMap.erase(productKey);
            deviceProfileMap.erase(productKey);
            deviceCommandMap.erase(productKey);
            deviceEventMap.erase(productKey);
        }
    }

    std::optional<contracts::DeviceProperty>
    ProfileCache::deviceProperty(const std::string &productKey, const std::string &identifier) {
        if (devicePropertyMap.find(productKey) == devicePropertyMap.end()) {
            return std::nullopt;
        }
        if (devicePropertyMap[productKey].find(identifier) == devicePropertyMap[productKey].end()) {
            return std::nullopt;
        }
        return devicePropertyMap[productKey][identifier];
    }

//    std::list<contracts::DeviceResource>
//    ProfileCache::deviceResourcesByRegex(const std::string &profileName, const std::string &regex) {
//        if (deviceResourceMap.find(profileName) == deviceResourceMap.end()) {
//            return {};
//        }
//        std::list<contracts::DeviceResource> res;
//        for (auto &resource: deviceResourceMap[profileName]) {
//            if (resource.second.name == regex) {
//                res.push_back(resource.second);
//                continue;
//            }
//            if (std::regex_match(resource.second.name, std::regex(regex))) {
//                res.push_back(resource.second);
//            }
//        }
//        return res;
//    }

    std::optional<contracts::DeviceCommand>
    ProfileCache::deviceCommand(const std::string& productKey, const std::string& commandIdentifier){
        if (deviceCommandMap.find(productKey) == deviceCommandMap.end()) {
            return std::nullopt;
        }
        if (deviceCommandMap[productKey].find(commandIdentifier) == deviceCommandMap[productKey].end()) {
            return std::nullopt;
        }
        return deviceCommandMap[productKey][commandIdentifier];
    }

//    std::optional<contracts::ResourceOperation>
//    ProfileCache::resourceOperation(const std::string &profileName, const std::string &deviceResource) {
//        if (deviceCommandMap.find(profileName) == deviceCommandMap.end()) {
//            return std::nullopt;
//        }
//        for (auto &command: deviceCommandMap[profileName]) {
//            if (!command.second.resourceOperations.empty()) {
//                for (auto &ro: command.second.resourceOperations) {
//                    if (ro.deviceResource == deviceResource) {
//                        return ro;
//                    }
//                }
//            }
//        }
//        return std::nullopt;
//    }


    void initCache(const std::string &instanceName, const std::string &baseServiceName,
                   std::shared_ptr<bootstrap::DiContainer> dic) {
        DeviceCache::newDeviceCache({});
        ProfileCache::newProfileCache({});
    }

    std::shared_ptr<DeviceCache> devices() {
        return dc;
    };

    std::shared_ptr<ProfileCache> profiles() {
        return pc;
    };

}
