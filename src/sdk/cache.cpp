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
        std::map<std::string, contracts::DeviceProfile> dpMap;
        std::map<std::string, std::map<std::string, contracts::DeviceResource>> drMap;
        std::map<std::string, std::map<std::string, contracts::DeviceCommand>> dcMap;
        for (auto &profile: profiles) {
            if (!profile.name.empty()) {
                dpMap[profile.name] = profile;
                std::map<std::string, contracts::DeviceResource> profileDeviceResourcesMap = {};
                for (auto &deviceResource: profile.deviceResources) {
                    profileDeviceResourcesMap[deviceResource.name] = deviceResource;
                }
                drMap[profile.name] = profileDeviceResourcesMap;
                std::map<std::string, contracts::DeviceCommand> profileDeviceCommandsMap = {};
                for (auto &deviceCommand: profile.deviceCommands) {
                    profileDeviceCommandsMap[deviceCommand.name] = deviceCommand;
                }
                dcMap[profile.name] = profileDeviceCommandsMap;
            }
        }
        pc = std::make_shared<ProfileCache>();
        pc->deviceProfileMap = dpMap;
        pc->deviceResourceMap = drMap;
        pc->deviceCommandMap = dcMap;
        return pc;
    }

    contracts::DeviceProfile *ProfileCache::forName(const std::string &name) {
        if (deviceProfileMap.find(name) != deviceProfileMap.end()) {
            return &deviceProfileMap[name];
        } else {
            return nullptr;
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
        auto profileName = profile.name;
        if (!profileName.empty()) {
            deviceProfileMap[profileName] = profile;
            std::map<std::string, contracts::DeviceResource> profileDeviceResourcesMap = {};
            for (auto &deviceResource: profile.deviceResources) {
                profileDeviceResourcesMap[deviceResource.name] = deviceResource;
            }
            deviceResourceMap[profileName] = profileDeviceResourcesMap;
            std::map<std::string, contracts::DeviceCommand> profileDeviceCommandsMap = {};
            for (auto &deviceCommand: profile.deviceCommands) {
                profileDeviceCommandsMap[deviceCommand.name] = deviceCommand;
            }
            deviceCommandMap[profileName] = profileDeviceCommandsMap;
        }
    }

    void ProfileCache::update(const contracts::DeviceProfile &profile) {
        removeByName(profile.name);
        add(profile);
    }

    void ProfileCache::removeByName(const std::string &name) {
        auto it = deviceProfileMap.find(name);
        if (it != deviceProfileMap.end()) {
            deviceProfileMap.erase(name);
            deviceResourceMap.erase(name);
            deviceCommandMap.erase(name);
        }
    }

    std::optional<contracts::DeviceResource>
    ProfileCache::deviceResource(const std::string &profileName, const std::string &resourceName) {
        if (deviceResourceMap.find(profileName) == deviceResourceMap.end()) {
            return std::nullopt;
        }
        if (deviceResourceMap[profileName].find(resourceName) == deviceResourceMap[profileName].end()) {
            return std::nullopt;
        }
        return deviceResourceMap[profileName][resourceName];
    }

    std::list<contracts::DeviceResource>
    ProfileCache::deviceResourcesByRegex(const std::string &profileName, const std::string &regex) {
        if (deviceResourceMap.find(profileName) == deviceResourceMap.end()) {
            return {};
        }
        std::list<contracts::DeviceResource> res;
        for (auto &resource: deviceResourceMap[profileName]) {
            if (resource.second.name == regex) {
                res.push_back(resource.second);
                continue;
            }
            if (std::regex_match(resource.second.name, std::regex(regex))) {
                res.push_back(resource.second);
            }
        }
        return res;
    }

    std::optional<contracts::DeviceCommand>
    ProfileCache::deviceCommand(const std::string &profileName, const std::string &commandName) {
        if (deviceCommandMap.find(profileName) == deviceCommandMap.end()) {
            return std::nullopt;
        }
        if (deviceCommandMap[profileName].find(commandName) == deviceCommandMap[profileName].end()) {
            return std::nullopt;
        }
        return deviceCommandMap[profileName][commandName];
    }

    std::optional<contracts::ResourceOperation>
    ProfileCache::resourceOperation(const std::string &profileName, const std::string &deviceResource) {
        if (deviceCommandMap.find(profileName) == deviceCommandMap.end()) {
            return std::nullopt;
        }
        for (auto &command: deviceCommandMap[profileName]) {
            if (!command.second.resourceOperations.empty()) {
                for (auto &ro: command.second.resourceOperations) {
                    if (ro.deviceResource == deviceResource) {
                        return ro;
                    }
                }
            }
        }
        return std::nullopt;
    }


    void initCache(const std::string &instanceName, const std::string &baseServiceName, bootstrap::DiContainer *dic) {
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
