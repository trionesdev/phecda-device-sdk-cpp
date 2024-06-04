//
// Created by fengxiaotx on 2024/5/21.
//
#include "phecda/sdk/DeviceServiceSDK.h"
#include "phecda/sdk/ProtocolDriver.h"
#include <boost/algorithm/string/trim.hpp>
#include "phecda/contracts/container.h"
#include "phecda/sdk/container.h"
#include "phecda/bootstrap/environement.h"


using namespace phecda::bootstrap;
using namespace phecda::contracts;

namespace phecda::sdk {

    void DeviceServiceSDK::setServiceName(std::string instanceName) {
        auto envValue = util::SystemUtils::getEnv("EnvInstanceName");
        if (!boost::trim_copy(envValue).empty()) {
            instanceName = envValue;
        }
        this->_baseServiceName = serviceKey_;
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

    void DeviceServiceSDK::addDevice(Device device) {
    }

    std::list<Device> DeviceServiceSDK::getDevices() {
        return {};
    }

    Device DeviceServiceSDK::getDeviceByName(std::string name) {
        return {};
    }

    void DeviceServiceSDK::updateDevice(Device device) {
    }

    void DeviceServiceSDK::removeDeviceByName(std::string name) {
    }

    void DeviceServiceSDK::addDeviceProfile(DeviceProfile profile) {
    }

    std::list<DeviceProfile> DeviceServiceSDK::deviceProfiles() {
        return std::list<DeviceProfile>();
    }

    DeviceProfile DeviceServiceSDK::getProfileByName(std::string name) {
        return DeviceProfile();
    }

    void DeviceServiceSDK::updateDeviceProfile(DeviceProfile profile) {
    }

    void DeviceServiceSDK::removeDeviceProfileByName(std::string name) {
    }

    DeviceResource DeviceServiceSDK::deviceResource(std::string deviceName, std::string resourceName) {
        return DeviceResource();
    }

    DeviceCommand DeviceServiceSDK::deviceCommand(std::string deviceName, std::string commandName) {
        return DeviceCommand();
    }

    void DeviceServiceSDK::addDeviceAutoEvent(std::string deviceName, std::string sourceName, AutoEvent autoEvent) {
    }

    void DeviceServiceSDK::removeDeviceAutoEvent(std::string deviceName, std::string autoEventName) {
    }

    void DeviceServiceSDK::run() {
        std::cout << "Hello, World! run" << std::endl;
        std::string instanceName = "";
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
        auto iValue = Variables::envVars.find("i");
        if (iValue != Variables::envVars.end()) {
            instanceName = iValue->second;
        }
        setServiceName(instanceName);
        config = new ConfigurationStruct();
        deviceService = new DeviceService();
        deviceService->name = serviceKey_;

        this->dic = Container::newContainer({
                                                    {configurationName,            config},
                                                    {contracts::container::deviceServiceName, deviceService},
                                                    {protocolDriverName,           driver}
                                            });
        auto wg = runAndReturnWaitGroup(args_,
                                        serviceKey_,
                                        config,
                                        startupTimer,
                                        dic,
                                        {

                                        });
        this->driver->start();
        wg->wait();
        std::cout << "ccc.maxEventSize:" << std::endl;
    }


    std::string DeviceServiceSDK::name() {
        return std::string();
    }

    bool DeviceServiceSDK::asyncReadingsEnabled() {
        return false;
    }

}
