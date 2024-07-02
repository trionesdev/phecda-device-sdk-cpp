//
// Created by fengxiaotx on 2024/6/27.
//
#include <phecda/contracts/model.h>
#include <phecda/util/StringUtils.h>
#include <phecda/util/TimeUtils.h>
#include <phecda/contracts/constants.h>
#include <nlohmann/json.hpp>
#include "phecda/sdk/model.h"
#include "phecda/log/log.h"


namespace phecda::contracts {
    static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("contracts.model"));

    BaseReading BaseReading::newBaseReading(
            const std::string &profileName,
            const std::string &deviceName,
            const std::string &resourceName,
            const std::string &valueType
    ) {
        auto baseReading = BaseReading();
        baseReading.id = util::StringUtils::uuid();
        baseReading.origin = util::TimeUtils::timestamp();
        baseReading.deviceName = deviceName;
        baseReading.resourceName = resourceName;
        baseReading.profileName = profileName;
        baseReading.valueType = valueType;
        return baseReading;
    }

    BaseReading ObjectReading::newObjectReading(const std::string &profileName, const std::string &deviceName,
                                                const std::string &resourceName, const std::any &objectValue) {
        auto baseReading = BaseReading::newBaseReading(profileName, deviceName, resourceName,
                                                       contracts::constants::VALUE_TYPE_STRUCT);
        baseReading.objectValue = objectValue;
        return baseReading;
    }

    BaseReading BinaryReading::newBinaryReading(const std::string &profileName, const std::string &deviceName,
                                                const std::string &resourceName,
                                                const std::vector<std::byte> &binaryValue,
                                                const std::string &mediaType) {
        auto baseReading = BaseReading::newBaseReading(profileName, deviceName, resourceName,
                                                       contracts::constants::VALUE_TYPE_BINARY);
        baseReading.binaryValue = binaryValue;
        baseReading.mediaType = mediaType;
        return baseReading;
    }

    std::string convertInterfaceValue(const std::string &valueType, std::any value) {
        try {
            if (valueType == constants::VALUE_TYPE_BOOL) {
                return std::any_cast<bool>(value) ? "true" : "false";
            } else if (valueType == constants::VALUE_TYPE_STRING) {
                return std::any_cast<std::string>(value);
            } else if (valueType == constants::VALUE_TYPE_INT) {
                return std::to_string(std::any_cast<int>(value));
            } else if (valueType == constants::VALUE_TYPE_FLOAT) {
                return std::to_string(std::any_cast<float>(value));
            } else if (valueType == constants::VALUE_TYPE_DOUBLE) {
                return std::to_string(std::any_cast<double>(value));
            } else if (
                    valueType == constants::VALUE_TYPE_STRING_ARRAY || valueType == constants::VALUE_TYPE_INT_ARRAY ||
                    valueType == constants::VALUE_TYPE_FLOAT_ARRAY || valueType == constants::VALUE_TYPE_DOUBLE_ARRAY) {
                //TODO array
                return "";
            } else {
                LOG_ERROR(logger, "invalid simple reading type of " + valueType);
                throw std::runtime_error("invalid simple reading type of " + valueType);
            }
        } catch (std::bad_any_cast &e) {
            LOG_ERROR(logger, "value convert error " + valueType);
            throw std::runtime_error("invalid simple reading type of " + valueType);
        }
    }

    BaseReading SimpleReading::newSimpleReading(const std::string &profileName, const std::string &deviceName,
                                                const std::string &resourceName, const std::string &valueType,
                                                std::any &value) {
        auto stringValue = convertInterfaceValue(valueType, value);
        auto baseReading = BaseReading::newBaseReading(profileName, deviceName, resourceName,
                                                       contracts::constants::VALUE_TYPE_BINARY);
        baseReading.value = stringValue;
        return baseReading;
    }

    Event Event::newEvent(std::string profileName, std::string deviceName, std::string sourceName) {
        Event event;
        event.id = util::StringUtils::uuid();
        event.origin = util::TimeUtils::timestamp();
        event.profileName = profileName;
        event.deviceName = deviceName;
        event.sourceName = sourceName;
        return event;
    }

    std::string Event::toJsonString() {
        nlohmann::json json;
        json["id"] = id;
        json["deviceName"] = deviceName;
        json["profileName"] = profileName;
        json["sourceName"] = sourceName;
        json["origin"] = origin;

        for (auto &reading: readings) {

            nlohmann::json objectValue;
            if (reading.objectValue.has_value()) {
                if (reading.objectValue.type().name() == typeid(int).name()) {
                    objectValue = std::any_cast<int>(reading.objectValue);
                }
                if (reading.objectValue.type().name() == typeid(long).name()) {
                    objectValue = std::any_cast<long>(reading.objectValue);
                }
                if (reading.objectValue.type().name() == typeid(float).name()) {
                    objectValue = std::any_cast<float>(reading.objectValue);
                }
                if (reading.objectValue.type().name() == typeid(double).name()) {
                    objectValue = std::any_cast<double>(reading.objectValue);
                }
                if (reading.objectValue.type().name() == typeid(std::string).name()) {
                    objectValue = std::any_cast<std::string>(reading.objectValue);
                }
            }

            nlohmann::json readingJson;
            readingJson["id"] = reading.id;
            readingJson["origin"] = reading.origin;
            readingJson["deviceName"] = reading.deviceName;
            readingJson["resourceName"] = reading.resourceName;
            readingJson["profileName"] = reading.profileName;
            readingJson["valueType"] = reading.valueType;
            readingJson["utils"] = reading.utils;
            readingJson["binaryValue"] = reading.binaryValue;
            readingJson["mediaType"] = reading.mediaType;
            readingJson["objectValue"] = objectValue;
            readingJson["value"] = reading.value;

            json["readings"].push_back(readingJson);
        }

        return json.dump();
    }
}

