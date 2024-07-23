//
// Created by fengxiaotx on 2024/5/22.
//
#include <string>
#include <optional>
#include <regex>
#include <phecda/bootstrap/di_container.h>
#include <phecda/contracts/model.h>

namespace phecda::sdk::cache {


    class DeviceCache {
    private:
        std::map<std::string, contracts::Device> deviceMap = {};
    public:


        static std::shared_ptr<DeviceCache> newDeviceCache(const std::list<contracts::Device> &devices);

        std::optional<contracts::Device> forName(const std::string &name);

        std::list<contracts::Device> all();

        void add(const contracts::Device &device);

        void update(const contracts::Device &device);

        void removeByName(const std::string &name);
    };

    class ProfileCache {
    private:
        std::map<std::string, contracts::DeviceProfile> deviceProfileMap = {};
//        std::map<std::string, std::map<std::string, contracts::DeviceResource>> deviceResourceMap = {};
        std::map<std::string, std::map<std::string, contracts::DeviceProperty>> devicePropertyMap = {};
        std::map<std::string, std::map<std::string, contracts::DeviceCommand>> deviceCommandMap = {};
        std::map<std::string, std::map<std::string, contracts::DeviceEvent>> deviceEventMap = {};
    public:
        static std::shared_ptr<ProfileCache> newProfileCache(const std::list<contracts::DeviceProfile> &profiles);

        std::optional<contracts::DeviceProfile> forName(const std::string &name);

        std::list<contracts::DeviceProfile> all();

        void add(const contracts::DeviceProfile &profile);

        void update(const contracts::DeviceProfile &profile);

        void removeByName(const std::string &name);

        std::optional<contracts::DeviceProperty>
        deviceProperty(const std::string &productKey, const std::string &identifier);

//        std::list<contracts::DeviceResource> deviceResourcesByRegex(const std::string& profileName, const std::string& regex);

        std::optional<contracts::DeviceCommand> deviceCommand(const std::string& productKey, const std::string& commandIdentifier);

//        std::optional<contracts::ResourceOperation>
//        resourceOperation(const std::string& profileName, const std::string& deviceResource);
    };

    static std::shared_ptr<DeviceCache> dc;
    static std::shared_ptr<ProfileCache> pc;

    void initCache(const std::string& instanceName, const std::string& baseServiceName, std::shared_ptr<bootstrap::DiContainer> dic);

    std::shared_ptr<DeviceCache> devices();

    std::shared_ptr<ProfileCache> profiles();
}