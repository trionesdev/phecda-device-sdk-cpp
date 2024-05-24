//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include "../bootstrap/Bootstrap.h"
#include "../bootstrap/environement.h"
#include "phecda/bootstrap/flags.h"
#include "phecda/sdk/AutoEventManager.h"
#include "phecda/sdk/config.h"
#include "phecda/sdk/DeviceServiceSDK.h"

using namespace phecda::bootstrap;

namespace phecda::sdk
{
    std::string _serviceVersion;
    std::string _serviceKey;
    std::string _baseServiceName;
    ProtocolDriver* _protocolDriver;
    AutoEventManager* autoEventManager;
    CommonArgs* argsInst;
    DeviceService* deviceService;
    ConfigurationStruct* config;
    Container* dic;

    void setServiceName(std::string instanceName)
    {
        auto envValue = std::getenv("EnvInstanceName");
        if (!envValue)
        {
            instanceName = envValue;
        }
        _baseServiceName = _serviceKey;
        if (!instanceName.empty())
        {
            _serviceKey = _serviceKey + "_" + instanceName;
        }
    }


    DeviceServiceSDK::DeviceServiceSDK(const std::string& serviceKey, const std::string& serviceVersion,
                                       ProtocolDriver* protocolDriver)
    {
        _serviceKey = serviceKey;
        _serviceVersion = serviceVersion;
        _protocolDriver = protocolDriver;
    }

    DeviceServiceSDK
    DeviceServiceSDK::newDeviceService(const std::string& serviceKey, const std::string& serviceVersion,
                                       ProtocolDriver* protocolDriver)
    {
        if (serviceKey.empty())
        {
            throw std::invalid_argument("please specify device service name");
        }
        if (serviceVersion.empty())
        {
            throw std::invalid_argument("please specify device service version");
        }
        return {serviceKey, serviceVersion, protocolDriver};
    }

    void DeviceServiceSDK::addDevice(Device device)
    {
    }

    std::list<Device> DeviceServiceSDK::getDevices()
    {
        return {};
    }

    Device DeviceServiceSDK::getDeviceByName(std::string name)
    {
        return {};
    }

    void DeviceServiceSDK::updateDevice(Device device)
    {
    }

    void DeviceServiceSDK::removeDeviceByName(std::string name)
    {
    }

    void DeviceServiceSDK::addDeviceProfile(DeviceProfile profile)
    {
    }

    std::list<DeviceProfile> DeviceServiceSDK::deviceProfiles()
    {
        return std::list<DeviceProfile>();
    }

    DeviceProfile DeviceServiceSDK::getProfileByName(std::string name)
    {
        return DeviceProfile();
    }

    void DeviceServiceSDK::updateDeviceProfile(DeviceProfile profile)
    {
    }

    void DeviceServiceSDK::removeDeviceProfileByName(std::string name)
    {
    }

    DeviceResource DeviceServiceSDK::deviceResource(std::string deviceName, std::string resourceName)
    {
        return DeviceResource();
    }

    DeviceCommand DeviceServiceSDK::deviceCommand(std::string deviceName, std::string commandName)
    {
        return DeviceCommand();
    }

    void DeviceServiceSDK::addDeviceAutoEvent(std::string deviceName, std::string sourceName, AutoEvent autoEvent)
    {
    }

    void DeviceServiceSDK::removeDeviceAutoEvent(std::string deviceName, std::string autoEventName)
    {
    }

    void DeviceServiceSDK::run()
    {
        std::cout << "Hello, World! run" << std::endl;
        std::string instanceName = "";
        std::string additionalUsage =
            " -i, --instance  Provides a service name suffix which allows unique instance to be created"
            "If the option is provided, service name will be replaced with \"<name>_<instance>\"";
        argsInst = CommonArgs::withUsage(additionalUsage);
        argsInst->parse(args);


        auto instance = envVars.find("instance");
        if (instance != envVars.end())
        {
            instanceName = instance->second;
        }
        auto iValue = envVars.find("i");
        if (iValue != envVars.end())
        {
            instanceName = iValue->second;
        }
        setServiceName(instanceName);
        config = new ConfigurationStruct();
        deviceService = new DeviceService{
            .name = _serviceKey
        };

        runAndReturnWaitGroup({});
    }


    std::string DeviceServiceSDK::name()
    {
        return std::string();
    }

    bool DeviceServiceSDK::asyncReadingsEnabled()
    {
        return false;
    }
}
