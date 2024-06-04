//
// Created by fengxiaotx on 2024/6/4.
//
#include <phecda/sdk/cache.h>

namespace phecda::sdk::cache {

    DeviceCache *DeviceCache::newDeviceCache(std::list<contracts::Device> devices) {
        return nullptr;
    }

    contracts::Device DeviceCache::forName(std::string name) {
        return contracts::Device();
    }

    std::list<contracts::Device> DeviceCache::all() {
        return std::list<contracts::Device>();
    }

    void DeviceCache::update(contracts::Device device) {

    }

    void DeviceCache::removeByName(std::string name) {

    }


    ProfileCache *ProfileCache::newProfileCache(std::list<contracts::DeviceProfile> profiles) {
        return nullptr;
    }

    contracts::DeviceProfile ProfileCache::forName(std::string name) {
        return contracts::DeviceProfile();
    }

    std::list<contracts::DeviceProfile> ProfileCache::all() {
        return std::list<contracts::DeviceProfile>();
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

    }

    void ProfileCache::removeByName(std::string name) {

    }

    contracts::DeviceResource ProfileCache::deviceResource(std::string profileName, std::string resourceName) {
        return contracts::DeviceResource();
    }

    contracts::DeviceResource ProfileCache::deviceResourcesByRegex(std::string profileName, std::string regex) {
        return contracts::DeviceResource();
    }

    contracts::DeviceCommand ProfileCache::deviceCommand(std::string profileName, std::string commandName) {
        return contracts::DeviceCommand();
    }

    contracts::ResourceOperation ProfileCache::resourceOperation(std::string profileName, std::string deviceResource) {
        return contracts::ResourceOperation();
    }


    void initCache(std::string instanceName, std::string baseServiceName, bootstrap::DiContainer *dic) {
        DeviceCache::newDeviceCache({});
        ProfileCache::newProfileCache({});
    }

    DeviceCache devices() {
        return dc;
    };

    ProfileCache profiles() {
        return pc;
    };

}
