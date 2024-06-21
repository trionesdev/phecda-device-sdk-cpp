//
// Created by fengxiaotx on 2024/6/17.
//
#include "phecda/sdk/application.h"
#include "phecda/contracts/container.h"
#include "phecda/sdk/container.h"
#include "phecda/contracts/errors.h"
#include "phecda/contracts/constants.h"
#include "phecda/sdk/constants.h"
#include "phecda/sdk/cache.h"
#include "phecda/sdk/transformer.h"
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>


namespace phecda::sdk::application {

    CommandValue createCommandValueFromDeviceResource(const contracts::DeviceResource &dr, std::any value) {
        auto result = CommandValue();
        std::string v = std::any_cast<std::string>(value);

        if (dr.properties.valueType != contracts::constants::VALUE_TYPE_STRING &&
            boost::algorithm::trim_copy(v).empty()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID,
                                                   "empty string is invalid for " + dr.properties.valueType +
                                                   " value type");
        }
        if (dr.properties.valueType == contracts::constants::VALUE_TYPE_BOOL) {
            result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_BOOL,
                                                   std::any_cast<bool>(v));
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_STRING) {
            result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_STRING,
                                                   std::any_cast<std::string>(v));
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_STRING) {
            result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_STRING,
                                                   v);
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_INT) {
            result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_STRING,
                                                   std::any_cast<int>(v));
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_LONG) {
            result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_STRING,
                                                   std::any_cast<long>(v));
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_FLOAT) {
            result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_STRING,
                                                   std::any_cast<float>(v));
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_DOUBLE) {
            result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_STRING,
                                                   std::any_cast<double>(v));
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_OBJECT) {
            result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_STRING,
                                                   v);
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_BOOL_ARRAY) {
            try {
                nlohmann::json json = nlohmann::json::parse(v);
                result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_BOOL_ARRAY,
                                                       json.get<std::list<bool>>());
            } catch (nlohmann::json::exception &e) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "failed to convert set parameter " + dr.properties.valueType +
                                                       " to ValueType " + dr.properties.valueType);
            }
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_STRING_ARRAY) {
            try {
                nlohmann::json json = nlohmann::json::parse(v);
                result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_STRING_ARRAY,
                                                       json.get<std::list<std::string>>());
            } catch (nlohmann::json::exception &e) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "failed to convert set parameter " + dr.properties.valueType +
                                                       " to ValueType " + dr.properties.valueType);
            }
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_INT_ARRAY) {
            try {
                nlohmann::json json = nlohmann::json::parse(v);
                result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_INT_ARRAY,
                                                       json.get<std::list<int>>());
            } catch (nlohmann::json::exception &e) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "failed to convert set parameter " + dr.properties.valueType +
                                                       " to ValueType " + dr.properties.valueType);
            }
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_LONG_ARRAY) {
            try {
                nlohmann::json json = nlohmann::json::parse(v);
                result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_LONG_ARRAY,
                                                       json.get<std::list<long>>());
            } catch (nlohmann::json::exception &e) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "failed to convert set parameter " + dr.properties.valueType +
                                                       " to ValueType " + dr.properties.valueType);
            }
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_FLOAT_ARRAY) {
            try {
                nlohmann::json json = nlohmann::json::parse(v);
                result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_FLOAT_ARRAY,
                                                       json.get<std::list<float>>());
            } catch (nlohmann::json::exception &e) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "failed to convert set parameter " + dr.properties.valueType +
                                                       " to ValueType " + dr.properties.valueType);
            }
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_DOUBLE_ARRAY) {
            try {
                nlohmann::json json = nlohmann::json::parse(v);
                result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_DOUBLE_ARRAY,
                                                       json.get<std::list<double>>());
            } catch (nlohmann::json::exception &e) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "failed to convert set parameter " + dr.properties.valueType +
                                                       " to ValueType " + dr.properties.valueType);
            }
        } else if (dr.properties.valueType == contracts::constants::VALUE_TYPE_OBJECT_ARRAY) {
            try {
                nlohmann::json json = nlohmann::json::parse(v);
                result = CommandValue::newCommandValue(dr.name, contracts::constants::VALUE_TYPE_OBJECT_ARRAY,
                                                       json);
            } catch (nlohmann::json::exception &e) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "failed to convert set parameter " + dr.properties.valueType +
                                                       " to ValueType " + dr.properties.valueType);
            }
        }
        return result;
    }

    std::optional<contracts::Event> readDeviceResource(
            const contracts::Device &device, const std::string &resourceName, const std::string &attributes,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        auto dr = cache::profiles()->deviceResource(device.profileName, resourceName);
        if (!dr.has_value()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_ENTITY_DOSE_NOT_EXIST,
                                                   "DeviceResource " + resourceName + " not found");
        }
        if (dr.value().properties.readWrite == contracts::constants::READ_WRITE_W) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_NOT_ALLOWED,
                                                   "DeviceResource " + resourceName + " is marked as write-only");
        }
        auto reqs = std::list<CommandRequest>();
        auto req = CommandRequest();
        req.deviceResourceName = dr->name;
        req.attributes = dr->attributes;
        req.type = dr->properties.valueType;
        if (!attributes.empty()) {
            if (req.attributes.empty()) {
                req.attributes = {};
            }
            req.attributes[constants::URLRawQuery] = attributes;
        }
        reqs.push_back(req);

        auto results = container::protocolDriverFrom(dic)->handleReadCommands(device.name, device.protocols, reqs);
        auto configuration = container::configurationFrom(dic);
        return transformer::commandValuesToEvent(results, device.name, dr->name, configuration->device.dataTransform,
                                                 dic);
    }

    std::optional<contracts::Event> readDeviceResourcesRegex(
            const contracts::Device &device, const std::string &regexResourceName, const std::string &attributes,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        auto deviceResources = cache::profiles()->deviceResourcesByRegex(device.profileName, regexResourceName);
        if (deviceResources.empty()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_ENTITY_DOSE_NOT_EXIST,
                                                   "Regex DeviceResource " + regexResourceName + " not found");
        }
        std::list<CommandRequest> reqs;
        for (auto &dr: deviceResources) {
            if (dr.properties.readWrite == contracts::constants::READ_WRITE_W) {
                continue;
            }
            auto req = CommandRequest();
            req.deviceResourceName = dr.name;
            req.attributes = dr.attributes;
            req.type = dr.properties.valueType;
            if (!attributes.empty()) {
                if (req.attributes.empty()) {
                    req.attributes = {};
                }
                req.attributes[constants::URLRawQuery] = attributes;
            }
            reqs.push_back(req);
        }
        if (reqs.empty()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_NOT_ALLOWED,
                                                   "no readable resources matched with " + regexResourceName);
        }
        auto results = container::protocolDriverFrom(dic)->handleReadCommands(device.name, device.protocols, reqs);
        auto configuration = sdk::container::configurationFrom(dic);
        return transformer::commandValuesToEvent(results, device.name, regexResourceName,
                                                 configuration->device.dataTransform, dic);
    }

    std::optional<contracts::Event> readDeviceCommand(
            const contracts::Device &device, const std::string &commandName, const std::string &attributes,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        auto dc = cache::profiles()->deviceCommand(device.profileName, commandName);
        if (!dc.has_value()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_ENTITY_DOSE_NOT_EXIST,
                                                   "DeviceCommand " + commandName + " not found");
        }
        if (dc->readWrite == contracts::constants::READ_WRITE_W) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_NOT_ALLOWED,
                                                   "DeviceCommand " + dc->name + " is marked as write-only");
        }
        auto configuration = sdk::container::configurationFrom(dic);
        if (dc->resourceOperations.size() > configuration->device.maxCmdOps) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                   "GET command " + dc->name + " exceed device " + device.name +
                                                   " MaxCmdOps (" + std::to_string(configuration->device.maxCmdOps) +
                                                   ")");
        }
        std::list<CommandRequest> reqs;
        for (auto &ro: dc->resourceOperations) {
            auto drName = ro.deviceResource;
            auto dr = cache::profiles()->deviceResource(device.profileName, drName);
            if (!dr.has_value()) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "DeviceResource " + drName + " in GET command " + dc->name +
                                                       " for " + device.name + " not defined");
            } else {
                auto req = CommandRequest();
                req.deviceResourceName = dr->name;
                req.attributes = dr->attributes;
                req.type = dr->properties.valueType;
                if (!attributes.empty()) {
                    if (req.attributes.empty()) {
                        req.attributes = {};
                    }
                    req.attributes[constants::URLRawQuery] = attributes;
                }
                reqs.push_back(req);
            }
        }

        auto results = container::protocolDriverFrom(dic)->handleReadCommands(device.name, device.protocols, reqs);
        return transformer::commandValuesToEvent(results, device.name, dc->name, configuration->device.dataTransform,
                                                 dic);
    }

    std::optional<contracts::Event> writeDeviceCommand(
            const contracts::Device &device, const std::string &commandName, const std::string &attributes,
            const std::map<std::string, std::any> &requests,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        auto dc = cache::profiles()->deviceCommand(device.profileName, commandName);
        if (!dc.has_value()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_ENTITY_DOSE_NOT_EXIST,
                                                   "DeviceCommand " + commandName + " not found");
        }
        if (dc->readWrite == contracts::constants::READ_WRITE_R) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_NOT_ALLOWED,
                                                   "DeviceCommand " + dc->name + " is marked as read-only");
        }
        auto configuration = sdk::container::configurationFrom(dic);
        if (dc->resourceOperations.size() > configuration->device.maxCmdOps) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                   "POST command " + dc->name + " exceed device " + device.name +
                                                   " MaxCmdOps (" + std::to_string(configuration->device.maxCmdOps) +
                                                   ")");
        }
        std::list<CommandValue> cvs = {};
        for (const auto &ro: dc->resourceOperations) {
            auto drName = ro.deviceResource;
            auto dr = cache::profiles()->deviceResource(device.profileName, drName);
            if (dr.has_value()) {
                std::any value;
                if (requests.find(ro.deviceResource) != requests.end()) {
                    value = requests.at(ro.deviceResource);
                } else {
                    if (ro.defaultValue.empty()) {
                        value = ro.defaultValue;
                    } else if (dr->properties.defaultValue.empty()) {
                        value = dr->properties.defaultValue;
                    } else {
                        throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                               "DeviceResource " + dr->name +
                                                               " not found in request body and no default value defined");
                    }
                }

                if (!ro.mappings.empty()) {
                    for (auto &m: ro.mappings) {
                        if (m.second == std::any_cast<string>(value)) {
                            value = m.first;
                            break;
                        }
                    }
                }
                auto cv = createCommandValueFromDeviceResource(dr.value(), value);
                cvs.push_back(cv);
            } else {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "DeviceResource " + drName + " in SET command " + dc->name +
                                                       " for " + device.name + " not defined");
            }

        }

        std::list<CommandRequest> reqs;
        if (!cvs.empty()) {
            for (auto &cv: cvs) {
                auto dr = cache::profiles()->deviceResource(device.profileName, cv.deviceResourceName);
                auto req = CommandRequest();
                req.deviceResourceName = cv.deviceResourceName;
                req.attributes = dr->attributes;
                req.type = cv.type;
                if (attributes.empty()) {
                    if (req.attributes.empty()) {
                        req.attributes = {};
                    }
                    req.attributes[constants::URLRawQuery] = attributes;
                }
            }
        }
        container::protocolDriverFrom(dic)->handleWriteCommands(device.name, device.protocols, reqs, cvs);
        if (dc->readWrite == contracts::constants::READ_WRITE_W) {
            return transformer::commandValuesToEvent(cvs, device.name, device.name, false,
                                                     dic);
        }
        return std::nullopt;
    }

    std::optional<contracts::Event> writeDeviceResource(
            const contracts::Device &device, const std::string &resourceName, const std::string &attributes,
            const std::map<std::string, std::any> &requests,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        auto dr = cache::profiles()->deviceResource(device.profileName, resourceName);
        if (!dr.has_value()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_ENTITY_DOSE_NOT_EXIST,
                                                   "resource " + resourceName + " not found");
        }
        if (dr->properties.readWrite == contracts::constants::READ_WRITE_R) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_NOT_ALLOWED,
                                                   "resource " + resourceName + " is marked as read-only");
        }
        auto v = requests.at(dr->name);
        if (requests.find(dr->name) == requests.end()) {
            if (dr->properties.defaultValue.empty()) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                       "DeviceResource " + dr->name +
                                                       " not found in request body and no default value defined");
            }
            v = dr->properties.defaultValue;
            auto cv = createCommandValueFromDeviceResource(dr.value(), v);
            auto req = CommandRequest();
            req.deviceResourceName = cv.deviceResourceName;
            req.attributes = dr->attributes;
            req.type = cv.type;
            if (attributes.empty()) {
                if (req.attributes.empty()) {
                    req.attributes = {};
                }
                req.attributes[phecda::sdk::constants::URLRawQuery] = attributes;
            }

            auto configuration = sdk::container::configurationFrom(dic);
            if (configuration->device.dataTransform) {
                sdk::transformer::transformWriteParameter(cv, dr->properties);
            }
            auto driver = sdk::container::protocolDriverFrom(dic);
            if (driver != nullptr) {
                driver->handleWriteCommands(device.name, device.protocols, {req}, {cv});
            }
            if (dr->properties.readWrite == contracts::constants::READ_WRITE_W) {
                return transformer::commandValuesToEvent({cv}, device.name, resourceName, false, dic);
            }
        }
        return std::nullopt;
    }


    std::optional<contracts::Device> validateServiceAndDeviceState(
            const std::string &deviceName, const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        auto ds = phecda::contracts::container::deviceServiceFrom(dic);
        if (ds->adminState == to_string(contracts::AdminState::LOCKED)) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVICE_LOCKED, "service locked");
        }
        auto device = cache::devices()->forName(deviceName);
        if (device.has_value()) {
            if (device->adminState == to_string(contracts::AdminState::LOCKED)) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVICE_LOCKED,
                                                       "device " + deviceName + " locked");
            }
            if (device->operatingState == to_string(contracts::OperatingState::DOWN)) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVICE_LOCKED,
                                                       "device " + deviceName + " OperatingState is DOWN");
            }
        }
        return device;
    }

     std::optional<contracts::Event> getCommand(
            const std::string &deviceName, const std::string &commandName, const std::string &queryParams,
            bool regexCmd,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        if (deviceName.empty()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID, "deviceName is empty");
        }
        if (commandName.empty()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID,
                                                   "commandName is empty");
        }
        auto device = validateServiceAndDeviceState(deviceName, dic);
        if (!device.has_value()) {
            return std::nullopt;
        }
        auto deviceCommand = cache::profiles()->deviceCommand(device->profileName, commandName);
        if (deviceCommand.has_value()) {
            return readDeviceCommand(device.value(), commandName, queryParams, dic);
        } else {
            if (regexCmd) {
                return readDeviceResourcesRegex(device.value(), commandName, queryParams, dic);
            } else {
                return readDeviceResource(device.value(), commandName, queryParams, dic);
            }
        }
    }

    std::optional<contracts::Event> setCommand(
            const std::string &deviceName, const std::string &commandName, const std::string &queryParams,
            const std::map<std::string, std::any> &requests,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        if (deviceName.empty()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID, "deviceName is empty");
        }
        if (commandName.empty()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID,
                                                   "commandName is empty");
        }
        auto device = validateServiceAndDeviceState(deviceName, dic);
        if (!device.has_value()) {
            return std::nullopt;
        }
        auto deviceCommand = cache::profiles()->deviceCommand(device->profileName, commandName);
        if (deviceCommand.has_value()) {
            return writeDeviceCommand(device.value(), commandName, queryParams, requests, dic);
        } else {
            return writeDeviceResource(device.value(), commandName, queryParams, requests, dic);
        }
    };

} // sdk
// phecda