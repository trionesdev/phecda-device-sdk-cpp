//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include <phecda/sdk/ProtocolDriver.h>
#include <phecda/contracts/constants.h>
#include <phecda/sdk/model.h>


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
        std::list<sdk::CommandValue> cvs = {};
        for (auto req: reqs) {
            if (req.type == phecda::contracts::constants::VALUE_TYPE_INT) {
                cvs.push_back(phecda::sdk::CommandValue::newCommandValue(req.deviceResourceName,
                                                                         phecda::contracts::constants::VALUE_TYPE_INT,
                                                                         1));
            } else if (req.type == phecda::contracts::constants::VALUE_TYPE_LONG) {
                cvs.push_back(phecda::sdk::CommandValue::newCommandValue(req.deviceResourceName,
                                                                         phecda::contracts::constants::VALUE_TYPE_LONG,
                                                                         100000000000));
            }
        }
        return cvs;
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