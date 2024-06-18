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
#include "phecda/sdk/service.h"


using namespace phecda::bootstrap;
using namespace phecda::contracts;

namespace phecda::sdk {

    void DeviceServiceSDK::setServiceName(std::string instanceName) {
        auto envValue = util::SystemUtils::getEnv("EnvInstanceName");
        if (!boost::trim_copy(envValue).empty()) {
            instanceName = envValue;
        }
        this->baseServiceName_ = serviceKey_;
        if (!boost::trim_copy(instanceName).empty()) {
            serviceKey_ = serviceKey_ + "_" + instanceName;
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
        return {};
    }

    void DeviceServiceSDK::addDevice(const Device& device) {
    }

    std::list<Device> DeviceServiceSDK::getDevices() {
        return {};
    }

    Device DeviceServiceSDK::getDeviceByName(const std::string& name) {
        return {};
    }

    void DeviceServiceSDK::updateDevice(const Device& device) {
    }

    void DeviceServiceSDK::removeDeviceByName(const std::string& name) {
    }

    void DeviceServiceSDK::addDeviceProfile(const DeviceProfile& profile) {
    }

    std::list<DeviceProfile> DeviceServiceSDK::deviceProfiles() {
        return std::list<DeviceProfile>();
    }

    DeviceProfile DeviceServiceSDK::getProfileByName(const std::string& name) {
        return DeviceProfile();
    }

    void DeviceServiceSDK::updateDeviceProfile(const DeviceProfile& profile) {
    }

    void DeviceServiceSDK::removeDeviceProfileByName(const std::string& name) {
    }

    DeviceResource DeviceServiceSDK::deviceResource(const std::string& deviceName, std::string resourceName) {
        return DeviceResource();
    }

    DeviceCommand DeviceServiceSDK::deviceCommand(const std::string& deviceName, std::string commandName) {
        return DeviceCommand();
    }

    void DeviceServiceSDK::addDeviceAutoEvent(const std::string& deviceName, const std::string& sourceName, const AutoEvent& autoEvent) {
    }

    void DeviceServiceSDK::removeDeviceAutoEvent(const std::string& deviceName, const std::string& autoEventName) {
    }

    void DeviceServiceSDK::run() {
        std::cout << "Hello, World! run" << std::endl;
        std::string instanceName;
        auto startupTimer = Timer::newStartUpTimer(serviceKey_);
        std::string additionalUsage =
                " -i, --instance  Provides a service name suffix which allows unique instance to be created"
                "If the option is provided, service name will be replaced with \"<name>_<instance>\"";
        args_ = CommonArgs::withUsage(additionalUsage);
        args_->parse(Variables::args);


        auto instance = Variables::envVars.find("instance");
        if (instance != Variables::envVars.end()) {
            instanceName = instance->second;
        }

        if (Variables::envVars.find("i") != Variables::envVars.end()) {
            instanceName = Variables::envVars["i"];
        }
        setServiceName(instanceName);
        config = std::make_shared<ConfigurationStruct>();
        deviceService = std::make_shared<DeviceService>();
        deviceService->name = serviceKey_;

        this->dic = DiContainer::newContainer({
                                                      {sdk::container::configurationName,               config},
                                                      {phecda::contracts::container::deviceServiceName, deviceService},
                                                      {sdk::container::protocolDriverName,              driver}
                                              });

        auto wg = runAndReturnWaitGroup(args_,
                                        serviceKey_,
                                        config,
                                        startupTimer,
                                        dic,
                                        {
                                                AutoEventManager::bootstrapHandler,
                                                [bootStrap = Bootstrap::newBootstrap(this)](auto args) {
                                                    return bootStrap->bootstrapHandler(
                                                            std::forward<decltype(args)>(args));
                                                },
                                                [bootstrap = MessagingBootstrap::newMessagingBootstrap(
                                                        baseServiceName_)](auto args) {
                                                    return bootstrap->bootstrapHandler(
                                                            std::forward<decltype(args)>(args));
                                                }
                                        });
        this->driver->start();
        wg->await();
    }


    std::string DeviceServiceSDK::name() {
        return std::string();
    }

    bool DeviceServiceSDK::asyncReadingsEnabled() {
        return false;
    }

}
