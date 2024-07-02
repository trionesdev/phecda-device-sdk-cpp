//
// Created by fengxiaotx on 2024/5/21.
//
#include "phecda/sdk/DeviceServiceSDK.h"
#include "phecda/sdk/ProtocolDriver.h"
#include "phecda/sdk/container.h"
#include "phecda/contracts/container.h"
#include "phecda/bootstrap/startup.h"
#include "phecda/bootstrap/bootstrap.h"
#include "phecda/sdk/auto_event.h"
#include "phecda/sdk/service_init.h"
#include "phecda/sdk/constants.h"


using namespace phecda::bootstrap;
using namespace phecda::contracts;

namespace phecda::sdk {

    void DeviceServiceSDK::setServiceName(std::string instanceName) {
        auto envValue = util::SystemUtils::getEnv("EnvInstanceName");
        if (!boost::trim_copy(envValue).empty()) {
            instanceName = envValue;
        }
        this->_baseServiceName = _serviceKey;
        if (!boost::trim_copy(instanceName).empty()) {
            _serviceKey = _serviceKey + "_" + instanceName;
        }
    }


    DeviceServiceSDK
    DeviceServiceSDK::newDeviceService(const std::string &serviceKey, const std::string &serviceVersion,
                                       ProtocolDriver *protocolDriver) {
        if (serviceKey.empty()) {
            throw std::invalid_argument("please specify device service name");
        }
        if (serviceVersion.empty()) {
            throw std::invalid_argument("please specify device service version");
        }
        phecda::sdk::constants::ServiceVersion = serviceVersion;
        DeviceServiceSDK deviceServiceSdk;
        deviceServiceSdk._serviceKey = serviceKey;
        deviceServiceSdk.driver = protocolDriver;
        deviceServiceSdk._config = std::make_shared<phecda::sdk::ConfigurationStruct>();
        return deviceServiceSdk;
    }

    void DeviceServiceSDK::addDevice(const Device &device) {
    }

    std::list<Device> DeviceServiceSDK::getDevices() {
        return {};
    }

    Device DeviceServiceSDK::getDeviceByName(const std::string &name) {
        return {};
    }

    void DeviceServiceSDK::updateDevice(const Device &device) {
    }

    void DeviceServiceSDK::removeDeviceByName(const std::string &name) {
    }

    void DeviceServiceSDK::addDeviceProfile(const DeviceProfile &profile) {
    }

    std::list<DeviceProfile> DeviceServiceSDK::deviceProfiles() {
        return std::list<DeviceProfile>();
    }

    DeviceProfile DeviceServiceSDK::getProfileByName(const std::string &name) {
        return DeviceProfile();
    }

    void DeviceServiceSDK::updateDeviceProfile(const DeviceProfile &profile) {
    }

    void DeviceServiceSDK::removeDeviceProfileByName(const std::string &name) {
    }

    DeviceResource DeviceServiceSDK::deviceResource(const std::string &deviceName, std::string resourceName) {
        return DeviceResource();
    }

    DeviceCommand DeviceServiceSDK::deviceCommand(const std::string &deviceName, std::string commandName) {
        return DeviceCommand();
    }

    void DeviceServiceSDK::addDeviceAutoEvent(const std::string &deviceName, const std::string &sourceName,
                                              const AutoEvent &autoEvent) {
    }

    void DeviceServiceSDK::removeDeviceAutoEvent(const std::string &deviceName, const std::string &autoEventName) {
    }

    void DeviceServiceSDK::run() {
        std::cout << "Hello, World! run" << std::endl;
        std::string instanceName;
        auto startupTimer = Timer::newStartUpTimer(_serviceKey);
        std::string additionalUsage =
                " -i, --instance  Provides a service name suffix which allows unique instance to be created"
                "If the option is provided, service name will be replaced with \"<name>_<instance>\"";
        _args = CommonArgs::withUsage(additionalUsage);
        _args->parse(Variables::args);


        auto instance = Variables::envVars.find("instance");
        if (instance != Variables::envVars.end()) {
            instanceName = instance->second;
        }

        if (Variables::envVars.find("i") != Variables::envVars.end()) {
            instanceName = Variables::envVars["i"];
        }
        setServiceName(instanceName);
        _config = std::make_shared<ConfigurationStruct>();
        _deviceService = std::make_shared<DeviceService>();
        _deviceService->name = _serviceKey;

        this->_dic = DiContainer::newContainer({
                                                      {sdk::container::configurationName,               _config},
                                                      {phecda::contracts::container::deviceServiceName, _deviceService},
                                                      {sdk::container::protocolDriverName,              driver}
                                              });

        auto wg = runAndReturnWaitGroup(_args,
                                        _serviceKey,
                                        _config,
                                        startupTimer,
                                        _dic,
                                        {
                                                AutoEventManager::bootstrapHandler,
                                                [bootStrap = Bootstrap::newBootstrap(this)](auto args) {
                                                    return bootStrap->bootstrapHandler(
                                                            std::forward<decltype(args)>(args));
                                                },
                                                [bootstrap = MessagingBootstrap::newMessagingBootstrap(
                                                        _baseServiceName)](auto args) {
                                                    return bootstrap->bootstrapHandler(
                                                            std::forward<decltype(args)>(args));
                                                }
                                        });
        this->driver->start();
        wg->await();
    }


    std::string DeviceServiceSDK::name() {
        return _serviceKey;
    }

    bool DeviceServiceSDK::asyncReadingsEnabled() {
        return false;
    }

    std::shared_ptr<MessagingClient> DeviceServiceSDK::messagingClient() {
        return std::shared_ptr<MessagingClient>();
    }

    void DeviceServiceSDK::sendEvent(const Event &event) {

    }

    void DeviceServiceSDK::senProperty(const Event &event) {

    }

}
