//
// Created by fengxiaotx on 2024/6/27.
//
#include <phecda/sdk/model.h>
#include <phecda/contracts/errors.h>
#include <phecda/contracts/constants.h>

namespace phecda::sdk {

    CommandValue CommandValue::newCommandValue(const std::string &deviceResourceName, const std::string &valueType,
                                               const std::any &value) {
        CommandValue cv;
        cv.deviceResourceName = deviceResourceName;
        cv.type = valueType;
        cv.value = value;
        return cv;
    }

    std::string CommandValue::toString() {
        return std::string();
    }

    std::string CommandValue::valueToString() {
        return std::any_cast<std::string>(value);
    }


    int CommandValue::intValue() {
        return std::any_cast<int>(value);
    }

    long CommandValue::longValue() {
        return std::any_cast<long>(value);
    }

    float CommandValue::floatValue() {
        return std::any_cast<float>(value);
    }

    double CommandValue::doubleValue() {
        return std::any_cast<double>(value);
    }

    std::vector<std::byte> CommandValue::binaryValue() {
        if (type != contracts::constants::VALUE_TYPE_BINARY) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                   "cannot convert CommandValue of " + type + " to " +
                                                   contracts::constants::VALUE_TYPE_BINARY);
        }
        return std::any_cast<std::vector<std::byte>>(value);
    }


}