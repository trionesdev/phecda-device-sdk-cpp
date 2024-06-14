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

    contracts::Device DeviceCache::forName(std::string name) {
        return this->deviceMap[name];
    }

    std::list<contracts::Device> DeviceCache::all() {
        std::list<contracts::Device> devices;
        for (auto &device: this->deviceMap) {
            devices.push_back(device.second);
        }
        return devices;
    }

    void DeviceCache::add(contracts::Device device) {
        if (!device.name.empty()) {
            deviceMap[device.name] = device;
        }
    }

    void DeviceCache::update(contracts::Device device) {
        if (!device.name.empty()) {
            deviceMap[device.name] = device;
        }
    }

    void DeviceCache::removeByName(std::string name) {
        deviceMap.erase(name);
    }


    std::shared_ptr<ProfileCache> ProfileCache::newProfileCache(std::list<contracts::DeviceProfile> profiles) {
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

    contracts::DeviceProfile* ProfileCache::forName(const std::string& name) {
        if (deviceProfileMap.find(name) != deviceProfileMap.end()){
            return &deviceProfileMap[name];
        } else{
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

    void ProfileCache::add(contracts::DeviceProfile profile) {
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

    void ProfileCache::update(contracts::DeviceProfile profile) {
        removeByName(profile.name);
        add(profile);
    }

    void ProfileCache::removeByName(std::string name) {
        auto it = deviceProfileMap.find(name);
        if (it != deviceProfileMap.end()) {
            deviceProfileMap.erase(name);
            deviceResourceMap.erase(name);
            deviceCommandMap.erase(name);
        }
    }

    contracts::DeviceResource ProfileCache::deviceResource(std::string profileName, std::string resourceName) {
        return deviceResourceMap[profileName][resourceName];
    }

    contracts::DeviceResource ProfileCache::deviceResourcesByRegex(std::string profileName, std::string regex) {
        return contracts::DeviceResource();
    }

    contracts::DeviceCommand ProfileCache::deviceCommand(std::string profileName, std::string commandName) {
        return deviceCommandMap[profileName][commandName];
    }

    contracts::ResourceOperation ProfileCache::resourceOperation(std::string profileName, std::string deviceResource) {
        return contracts::ResourceOperation();
    }


    void initCache(std::string instanceName, std::string baseServiceName, bootstrap::DiContainer *dic) {
        DeviceCache::newDeviceCache({});
        ProfileCache::newProfileCache({});
    }

    DeviceCache *devices() {
//        return DeviceCache::dc;
        return {};
    };

    ProfileCache *profiles() {
//        return ProfileCache::pc;
        return {};
    };

}
