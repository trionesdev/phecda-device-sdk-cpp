//
// Created by fengxiaotx on 2024/5/22.
//
#include <string>
#include <phecda/bootstrap/di-container.h>
#include <phecda/contracts/model.h>

namespace phecda::sdk::cache {


    class DeviceCache {
    private:
        std::map<std::string, contracts::Device> deviceMap = {};
    public:


        static std::shared_ptr<DeviceCache> newDeviceCache(const std::list<contracts::Device> &devices);

        contracts::Device forName(std::string name);

        std::list<contracts::Device> all();

        void add(contracts::Device device);

        void update(contracts::Device device);

        void removeByName(std::string name);
    };

    class ProfileCache {
    private:
        std::map<std::string, contracts::DeviceProfile> deviceProfileMap = {};
        std::map<std::string, std::map<std::string, contracts::DeviceResource>> deviceResourceMap = {};
        std::map<std::string, std::map<std::string, contracts::DeviceCommand>> deviceCommandMap = {};
    public:
        static std::shared_ptr<ProfileCache> newProfileCache(std::list<contracts::DeviceProfile> profiles);

        contracts::DeviceProfile *forName(const std::string &name);

        std::list<contracts::DeviceProfile> all();

        void add(contracts::DeviceProfile profile);

        void update(contracts::DeviceProfile profile);

        void removeByName(std::string name);

        contracts::DeviceResource deviceResource(std::string profileName, std::string resourceName);

        contracts::DeviceResource deviceResourcesByRegex(std::string profileName, std::string regex);

        contracts::DeviceCommand deviceCommand(std::string profileName, std::string commandName);

        contracts::ResourceOperation resourceOperation(std::string profileName, std::string deviceResource);
    };

    static std::shared_ptr<DeviceCache> dc;
    static std::shared_ptr<ProfileCache> pc;

    void initCache(std::string instanceName, std::string baseServiceName, bootstrap::DiContainer *dic);

    DeviceCache *devices();

    ProfileCache *profiles();
}