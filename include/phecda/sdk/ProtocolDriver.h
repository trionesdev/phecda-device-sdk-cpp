//
// Created by fengxiaotx on 2024/5/21.
//

#ifndef PHECDA_DEVICE_SDK_APP_PRPTOCOLDRIVER_H
#define PHECDA_DEVICE_SDK_APP_PRPTOCOLDRIVER_H

#include <phecda/sdk/DeviceServiceSDK.h>
#include "model.h"


namespace phecda::sdk {
//    class DeviceServiceSDK;
    class ProtocolDriver {
    public:
        void initialize(DeviceServiceSDK *sdk);

        void start();

        void stop(bool force);

        std::list<CommandValue>
        handleReadCommands(std::string deviceName, std::map<std::string, std::map<std::string, std::any>> protocols,
                           std::list<CommandRequest> reqs);

        void
        handleWriteCommands(std::string deviceName, std::map<std::string, std::map<std::string, std::any>> protocols,
                            std::list<CommandRequest> reqs, std::list<CommandValue> params);

        void addDevice(std::string deviceName, std::map<std::string, std::map<std::string, std::any>> protocols,
                       std::string adminState);

        void updateDevice(std::string deviceName, std::map<std::string, std::map<std::string, std::any>> protocols,
                          std::string adminState);

        void removeDevice(std::string deviceName, std::map<std::string, std::any> protocols);
    };
}
#endif //PHECDA_DEVICE_SDK_APP_PRPTOCOLDRIVER_H
