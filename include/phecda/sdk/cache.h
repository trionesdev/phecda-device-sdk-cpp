//
// Created by fengxiaotx on 2024/5/22.
//
#include <string>
#include <phecda/bootstrap/di-container.h>
#include <phecda/contracts/model.h>

namespace phecda::sdk {


    class DeviceCache {
    public:
        static DeviceCache* newDeviceCache(std::list<contracts::Device> devices);
        contracts::Device forName(std::string name);
        std::list<contracts::Device> all();
        void update(contracts::Device device);
        void removeByName(std::string name);
    };

    class ProfileCache {
    public:
        static ProfileCache* newProfileCache(std::list<contracts::DeviceProfile> profiles);
        contracts::DeviceProfile forName(std::string name);
        std::list<contracts::DeviceProfile> all();
        void add(contracts::DeviceProfile profile);
        void update(contracts::DeviceProfile profile);
        void removeByName(std::string name);
        contracts::DeviceResource deviceResource(std::string profileName, std::string resourceName);
        contracts::DeviceResource deviceResourcesByRegex(std::string profileName, std::string regex);
        contracts::DeviceCommand deviceCommand(std::string profileName, std::string commandName);
        contracts::ResourceOperation resourceOperation(std::string profileName, std::string deviceResource);
    };

    static DeviceCache dc;
    static ProfileCache pc;

    static void initCache(std::string instanceName, std::string baseServiceName, bootstrap::DiContainer *dic);
    static DeviceCache devices();
    static ProfileCache profiles();
}