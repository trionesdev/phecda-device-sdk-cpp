//
// Created by fengxiaotx on 2024/5/21.
//

#ifndef PHECDA_DEVICE_SDK_DEVICESDK_H
#define PHECDA_DEVICE_SDK_DEVICESDK_H


#include "phecda/contracts/model.h"
#include "phecda/bootstrap/flags.h"
#include "config.h"
#include "phecda/bootstrap/di-container.h"

using namespace phecda::bootstrap;
using namespace phecda::contracts;

namespace phecda::sdk {
    class ProtocolDriver;  //向前申明
    class DeviceServiceSDK {
    private:
        std::string _serviceVersion;
        std::string serviceKey_;
        std::string _baseServiceName;
        ProtocolDriver *driver;
        AutoEvent *_autoEventManager;
        CommonArgs *args_;
        DeviceService *deviceService;
        ConfigurationStruct *config;
        DiContainer *dic;
        void setServiceName(std::string instanceName);
    public:

        static DeviceServiceSDK newDeviceService(const std::string &serviceKey, const std::string &serviceVersion,
                                                 ProtocolDriver *protocolDriver);

        void addDevice(Device device);

        std::list<Device> getDevices();

        Device getDeviceByName(std::string name);

        void updateDevice(Device device);

        void removeDeviceByName(std::string name);

        void addDeviceProfile(DeviceProfile profile);

        std::list<DeviceProfile> deviceProfiles();

        DeviceProfile getProfileByName(std::string name);

        void updateDeviceProfile(DeviceProfile profile);

        void removeDeviceProfileByName(std::string name);

        DeviceResource deviceResource(std::string deviceName, std::string resourceName);

        DeviceCommand deviceCommand(std::string deviceName, std::string commandName);

        void addDeviceAutoEvent(std::string deviceName, std::string sourceName, AutoEvent autoEvent);

        void removeDeviceAutoEvent(std::string deviceName, std::string autoEventName);

        void run();

        std::string name();

        bool asyncReadingsEnabled();

    };


}
#endif //PHECDA_DEVICE_SDK_CPP_DEVICESDK_H
