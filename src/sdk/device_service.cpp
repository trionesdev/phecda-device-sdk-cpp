//
// Created by fengxiaotx on 2024/5/21.
//
#include <nlohmann/json.hpp>
#include "phecda/sdk/DeviceServiceSDK.h"
#include "phecda/sdk/ProtocolDriver.h"
#include "phecda/sdk/container.h"
#include "phecda/contracts/container.h"
#include "phecda/sdk/service_init.h"
#include "phecda/sdk/constants.h"
#include "phecda/sdk/cache.h"
#include "phecda/contracts/errors.h"
#include <phecda/log/log.h>


using namespace phecda::bootstrap;
using namespace phecda::contracts;

namespace phecda::sdk {
    static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sdk/device_service"));
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

    void DeviceServiceSDK::addDevice(Device device) {
        auto deviceCache = cache::devices()->forName(device.name);
        if (deviceCache.has_value()) {
            throw CommonPhecdaException(error_kind::KIND_DUPLICATE_NAME,
                                        "name conflicted, Device " + device.name + " exists");
        }
        device.serviceName = _serviceKey;
    }

    std::list<Device> DeviceServiceSDK::getDevices() {
        return cache::devices()->all();
    }

    std::optional<Device> DeviceServiceSDK::getDeviceByName(const std::string &name) {
        return cache::devices()->forName(name);
    }

    void DeviceServiceSDK::updateDevice(const Device &device) {
        cache::devices()->update(device);
    }

    void DeviceServiceSDK::removeDeviceByName(const std::string &name) {
        cache::devices()->removeByName(name);
    }

    void DeviceServiceSDK::addDeviceProfile(const DeviceProfile &profile) {
        cache::profiles()->add(profile);
    }

    std::list<DeviceProfile> DeviceServiceSDK::deviceProfiles() {
        return cache::profiles()->all();
    }

    std::optional<DeviceProfile> DeviceServiceSDK::getProfileByProductKey(const std::string &productKey) {
        return cache::profiles()->forProductKey(productKey);
    }

    void DeviceServiceSDK::updateDeviceProfile(const DeviceProfile &profile) {
        cache::profiles()->update(profile);
    }

    void DeviceServiceSDK::removeDeviceProfileByProductKey(const std::string &productKey) {
        cache::profiles()->removeByProductKey(productKey);
    }

    std::optional<DeviceProperty>
    DeviceServiceSDK::deviceProperty(const std::string &deviceName, const std::string &identifier) {
        auto device = cache::devices()->forName(deviceName);
        if (device.has_value()) {
            if (device->productKey.empty()) {
                return cache::profiles()->deviceProperty(device->productKey, identifier);
            }
        }
        return std::nullopt;
    }

    std::optional<DeviceCommand>
    DeviceServiceSDK::deviceCommand(const std::string &deviceName, const std::string &commandName) {
        auto device = cache::devices()->forName(deviceName);
        if (device.has_value()) {
            if (device->productKey.empty()) {
                return cache::profiles()->deviceCommand(device->productKey, commandName);
            }
        }
        return std::nullopt;
    }

    void DeviceServiceSDK::addDeviceAutoEvent(const std::string &deviceName, const std::string &sourceName,
                                              const AutoEvent &autoEvent) {
    }

    void DeviceServiceSDK::removeDeviceAutoEvent(const std::string &deviceName, const std::string &autoEventName) {
    }

    void DeviceServiceSDK::run() {
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
        LOG_INFO(logger, "Starting device service: " << _serviceKey);

        this->driver->start();
        wg->await();
    }


    std::string DeviceServiceSDK::name() const {
        return _serviceKey;
    }

    bool DeviceServiceSDK::asyncReadingsEnabled() const {
        return _config->device.enableAsyncReadings;
    }

    std::shared_ptr<MessagingClient> DeviceServiceSDK::messagingClient() {
        return container::messagingClientFrom(_dic);
    }

    void DeviceServiceSDK::sendEvent( const Event& event) {
        auto messagingClient = container::messagingClientFrom(_dic);
        auto phecdaEvent  = PhecdaEvent::newPhecdaEvent(event);
    }

    void DeviceServiceSDK::sendProperty(const Event &event) {
        auto messagingClient = container::messagingClientFrom(_dic);
    }

}
