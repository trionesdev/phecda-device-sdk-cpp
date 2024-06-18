//
// Created by fengxiaotx on 2024/5/21.
//

#ifndef PHECDA_DEVICE_SDK_DEVICESDK_H
#define PHECDA_DEVICE_SDK_DEVICESDK_H


#include "phecda/contracts/model.h"
#include "phecda/bootstrap/flags.h"
#include "config.h"
#include "phecda/bootstrap/di-container.h"
#include "phecda/sdk/auto_event.h"

using namespace phecda::bootstrap;
using namespace phecda::contracts;

namespace phecda::sdk {
    class ProtocolDriver;  //向前申明
    class DeviceServiceSDK {
    private:
        std::string _serviceVersion;
        CommonArgs *args_;
        DeviceService *deviceService;

        std::shared_ptr<DiContainer> dic;

        void setServiceName(std::string instanceName);

    public:
        std::string serviceKey_;
        std::string baseServiceName_;
        ProtocolDriver *driver;
        std::shared_ptr<AutoEventManager> autoEventManager_;
        ConfigurationStruct *config;

        static DeviceServiceSDK newDeviceService(const std::string &serviceKey, const std::string &serviceVersion,
                                                 ProtocolDriver *protocolDriver);

        void addDevice(const Device &device);

        std::list<Device> getDevices();

        Device getDeviceByName(const std::string &name);

        void updateDevice(const Device &device);

        void removeDeviceByName(const std::string &name);

        void addDeviceProfile(const DeviceProfile &profile);

        std::list<DeviceProfile> deviceProfiles();

        DeviceProfile getProfileByName(const std::string &name);

        void updateDeviceProfile(const DeviceProfile &profile);

        void removeDeviceProfileByName(const std::string &name);

        DeviceResource deviceResource(const std::string &deviceName, std::string resourceName);

        DeviceCommand deviceCommand(const std::string &deviceName, std::string commandName);

        void
        addDeviceAutoEvent(const std::string &deviceName, const std::string &sourceName, const AutoEvent &autoEvent);

        void removeDeviceAutoEvent(const std::string &deviceName, const std::string &autoEventName);

        void run();

        std::string name();

        bool asyncReadingsEnabled();

    };


}
#endif //PHECDA_DEVICE_SDK_CPP_DEVICESDK_H
