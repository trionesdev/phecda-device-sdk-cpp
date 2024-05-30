//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include <phecda/sdk/ProtocolDriver.h>


namespace phecda {
    void sdk::ProtocolDriver::initialize(sdk::DeviceServiceSDK *sdk) {
        std::cout << "Hello, World! initialize" << std::endl;

    }

    void sdk::ProtocolDriver::start() {

    }

    void sdk::ProtocolDriver::stop(bool force) {

    }

    std::list<sdk::CommandValue> sdk::ProtocolDriver::handleReadCommands(std::string deviceName,
                                                               std::map<std::string, std::map<std::string, std::any>> protocols,
                                                               list<CommandRequest> reqs) {
        return list<CommandValue>();
    }

    void sdk::ProtocolDriver::handleWriteCommands(std::string deviceName,
                                                  std::map<std::string, std::map<std::string, std::any>> protocols,
                                                  list<CommandRequest> reqs, list<CommandValue> params) {

    }

    void sdk::ProtocolDriver::addDevice(std::string deviceName,
                                        std::map<std::string, std::map<std::string, std::any>> protocols,
                                        std::string adminState) {

    }

    void sdk::ProtocolDriver::updateDevice(std::string deviceName,
                                           std::map<std::string, std::map<std::string, std::any>> protocols,
                                           std::string adminState) {

    }

    void sdk::ProtocolDriver::removeDevice(std::string deviceName, std::map<std::string, std::any> protocols) {

    }


}