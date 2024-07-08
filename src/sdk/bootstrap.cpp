//
// Created by fengxiaotx on 2024/5/21.
//
#include "phecda/sdk/ProtocolDriver.h"
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/logmanager.h>
#include <phecda/log/log.h>

namespace phecda::sdk
{
    static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sdk/bootstrap"));

    void bootstrap(std::string args[], const std::string& serviceKey, const std::string& serviceVersion,
                   ProtocolDriver* protocolDriver)
    {
        LOG_INFO(logger, "Phecda Device Driver starting .....");
        DeviceServiceSDK deviceService = DeviceServiceSDK::newDeviceService(serviceKey, serviceVersion, protocolDriver);
        deviceService.run();
    }
}
