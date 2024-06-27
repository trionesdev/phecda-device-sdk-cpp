//
// Created by fengxiaotx on 2024/6/27.
//
#include <phecda/contracts/model.h>
#include <phecda/util/StringUtils.h>
#include <phecda/util/TimeUtils.h>
#include <phecda/contracts/constants.h>
#include <nlohmann/json.hpp>
#include "phecda/sdk/model.h"


namespace phecda::contracts {


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
                                                       contracts::constants::VALUE_TYPE_OBJECT);
        baseReading.objectValue = objectValue;
        return baseReading;
    }

    BaseReading BinaryReading::newBinaryReading(const std::string &profileName, const std::string &deviceName,
                                                const std::string &resourceName, const std::vector<std::byte> &binaryValue,
                                                const std::string &mediaType) {
        auto baseReading = BaseReading::newBaseReading(profileName, deviceName, resourceName,
                                                       contracts::constants::VALUE_TYPE_BINARY);
        baseReading.binaryValue = binaryValue;
        baseReading.mediaType = mediaType;
        return baseReading;
    }

    std::string convertInterfaceValue(const std::string& valueType, std::any value) {
        if (valueType == constants::VALUE_TYPE_BOOL) {
            return std::any_cast<bool>(value) ? "true" : "false";
        } else if (valueType == constants::VALUE_TYPE_STRING || valueType == constants::VALUE_TYPE_INT ||
                   valueType == constants::VALUE_TYPE_FLOAT || valueType == constants::VALUE_TYPE_DOUBLE) {
            return std::any_cast<std::string>(value);
        } else if (
                valueType == constants::VALUE_TYPE_STRING_ARRAY || valueType == constants::VALUE_TYPE_INT_ARRAY ||
                valueType == constants::VALUE_TYPE_FLOAT_ARRAY || valueType == constants::VALUE_TYPE_DOUBLE_ARRAY) {
            return "";
        } else {
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
}

