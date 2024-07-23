//
// Created by fengxiaotx on 2024/6/18.
//
#include "phecda/sdk/transformer.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include "phecda/contracts/errors.h"
#include "phecda/contracts/constants.h"
#include <phecda/sdk/cache.h>
#include <phecda/contracts/model.h>
#include <phecda/sdk/common_utils.h>

namespace phecda::sdk::transformer {

    long long uniqueOrigin() {
        auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
        );
        return currentTime.count();
    }

    bool isNan(CommandValue cv) {
        if (cv.type == contracts::constants::VALUE_TYPE_FLOAT) {
            auto v = cv.floatValue();
            return std::isnan(v);
        }
        if (cv.type == contracts::constants::VALUE_TYPE_DOUBLE) {
            auto v = cv.doubleValue();
            return std::isnan(v);
        }
        return false;
    }

    bool isNumericValueType(const CommandValue &cv) {
        if (cv.type == contracts::constants::VALUE_TYPE_INT || cv.type == contracts::constants::VALUE_TYPE_LONG
            || cv.type == contracts::constants::VALUE_TYPE_FLOAT ||
            cv.type == contracts::constants::VALUE_TYPE_DOUBLE) {
            return true;
        } else {
            return false;
        }
    }

    bool checkTransformedValueInRange(const std::any &origin, double transformed) {
        bool isRange = false;
        int minValue = std::numeric_limits<int>::min();
        int maxValue = std::numeric_limits<int>::max();
        if (origin.type().name() == typeid(int).name()) {
            if (transformed >= minValue || transformed <= maxValue) {
                isRange = true;
            }
        }
        return isRange;
    }

    std::any transformBase(std::any value, double base, bool read) {
        double doubleValue = 0.0;
        if (value.type().name() == typeid(int).name()) {
            doubleValue = static_cast<double>(std::any_cast<int>(value));
        } else if (value.type().name() == typeid(long).name()) {
            doubleValue = static_cast<double>(std::any_cast<long>(value));
        } else if (value.type().name() == typeid(float).name()) {
            doubleValue = static_cast<double>(std::any_cast<float>(value));
        } else if (value.type().name() == typeid(double).name()) {
            doubleValue = std::any_cast<double>(value);
        }
        if (read) {
            doubleValue = pow(base, doubleValue);
        } else {
            doubleValue = std::log(doubleValue) / std::log(base);
        }
        auto inRange = checkTransformedValueInRange(value, doubleValue);
        if (!inRange) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_OVERFLOW_ERROR,
                                                   "transformed value out of its original type (" +
                                                   std::any_cast<std::string>(value) + ") range");
        }
        if (value.type().name() == typeid(int).name()) {
            return static_cast<int>(doubleValue);
        } else if (value.type().name() == typeid(long).name()) {
            return static_cast<long>(doubleValue);
        } else if (value.type().name() == typeid(float).name()) {
            return static_cast<float>(doubleValue);
        } else if (value.type().name() == typeid(double).name()) {
            return doubleValue;
        } else {
            return value;
        }
    }

    std::any transformScale(std::any value, double scale, bool read) {
        double valueDouble;
        if (value.type().name() == typeid(int).name()) {
            valueDouble = std::any_cast<int>(value);
        } else if (value.type().name() == typeid(long).name()) {
            valueDouble = std::any_cast<long>(value);
        } else if (value.type().name() == typeid(float).name()) {
            valueDouble = std::any_cast<float>(value);
        } else if (value.type().name() == typeid(double).name()) {
            valueDouble = std::any_cast<double>(value);
        } else {
            return value;
        }
        if (read) {
            return valueDouble * scale;
        } else {
            return valueDouble / scale;
        }
        auto inRange = checkTransformedValueInRange(value, valueDouble);
        if (!inRange) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_OVERFLOW_ERROR,
                                                   "transformed value out of its original type (" +
                                                   std::any_cast<std::string>(value) + ") range");
        }
        if (value.type().name() == typeid(int).name()) {
            if (read) {
                return std::any_cast<int>(value) * scale;
            } else {
                return std::any_cast<int>(value) / scale;
            }
        }
        if (value.type().name() == typeid(long).name()) {
            if (read) {
                return std::any_cast<long>(value) * scale;
            } else {
                return std::any_cast<long>(value) / scale;
            }
        }
        if (value.type().name() == typeid(float).name()) {
            if (read) {
                return std::any_cast<float>(value) * scale;
            } else {
                return std::any_cast<float>(value) / scale;
            }
        }

        if (value.type().name() == typeid(double).name()) {
            if (read) {
                return std::any_cast<double>(value) * scale;
            } else {
                return std::any_cast<double>(value) / scale;
            }
        }
        return value;
    }

    std::any transformOffset(std::any value, double offset, bool read) {
        auto valueDouble = std::any_cast<double>(value);
        if (read) {
            return valueDouble + offset;
        } else {
            return valueDouble - offset;
        }
        auto inRange = checkTransformedValueInRange(value, valueDouble);
        if (!inRange) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_OVERFLOW_ERROR,
                                                   "transformed value out of its original type (" +
                                                   std::any_cast<std::string>(value) + ") range");
        }
        if (value.type().name() == typeid(int).name()) {
            if (read) {
                return std::any_cast<int>(value) + offset;
            } else {
                return std::any_cast<int>(value) - offset;
            }
        }
        if (value.type().name() == typeid(long).name()) {
            if (read) {
                return std::any_cast<long>(value) + offset;
            } else {
                return std::any_cast<long>(value) - offset;
            }
        }
        if (value.type().name() == typeid(float).name()) {
            if (read) {
                return std::any_cast<float>(value) + offset;
            } else {
                return std::any_cast<float>(value) - offset;
            }
        }
        if (value.type().name() == typeid(double).name()) {
            if (read) {
                return std::any_cast<double>(value) + offset;
            } else {
                return std::any_cast<double>(value) - offset;
            }
        }
        return value;
    }

    std::any transformReadMask(std::any value, long mask) {
        if (value.type().name() == typeid(int).name()) {
            return std::any_cast<int>(value) & mask;
        } else if (value.type().name() == typeid(long).name()) {
            return std::any_cast<long>(value) & mask;
        }
        return value;
    }

    std::any transformReadShift(std::any value, long shift) {
        if (value.type().name() == typeid(int).name()) {
            if (shift > 0) {
                return std::any_cast<int>(value) >> shift;
            } else {
                return std::any_cast<int>(value) << -shift;
            }
        } else if (value.type().name() == typeid(long).name()) {
            if (shift > 0) {
                return std::any_cast<long>(value) >> shift;
            } else {
                return std::any_cast<long>(value) << -shift;
            }
        }
        return value;
    }

    std::any commandValueForTransform(CommandValue cv) {
        if (cv.type == contracts::constants::VALUE_TYPE_INT) {
            return cv.intValue();
        } else if (cv.type == contracts::constants::VALUE_TYPE_LONG) {
            return cv.longValue();
        } else if (cv.type == contracts::constants::VALUE_TYPE_FLOAT) {
            return cv.floatValue();
        } else if (cv.type == contracts::constants::VALUE_TYPE_DOUBLE) {
            return cv.doubleValue();
        } else {
            return nullptr;
        }
    }

    void validateWriteMaximum(const std::any &value, double maximum) {
        if (value.type().name() == typeid(int).name()) {
            if (std::any_cast<int>(value) > maximum) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID,
                                                       "set command parameter out of maximum value" +
                                                       std::to_string(maximum));
            }
        }
        if (value.type().name() == typeid(long).name()) {
            if (std::any_cast<long>(value) > maximum) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID,
                                                       "set command parameter out of maximum value" +
                                                       std::to_string(maximum));
            }
        }
    };

    void validateWriteMinimum(const std::any &value, double maximum) {
        if (value.type().name() == typeid(int).name()) {
            if (std::any_cast<int>(value) < maximum) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID,
                                                       "set command parameter out of minimum value" +
                                                       std::to_string(maximum));
            }
        }
        if (value.type().name() == typeid(long).name()) {
            if (std::any_cast<long>(value) < maximum) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_CONTRACT_INVALID,
                                                       "set command parameter out of minimum value" +
                                                       std::to_string(maximum));
            }
        }
    };

    void transformWriteParameter(CommandValue cv, const contracts::ResourceProperties &pv) {
        if (!isNumericValueType(cv)) {
            return;
        }
        auto value = commandValueForTransform(cv);
        auto newValue = value;
        if (pv.maximum != 0) {
            validateWriteMaximum(value, pv.maximum);
        }
        if (pv.minimum != 0) {
            validateWriteMinimum(value, pv.minimum);
        }
        if (pv.offset != 0) {
            if (pv.offset != defaultOffset) {
                newValue = transformOffset(newValue, pv.offset, false);
            }
        }
        if (pv.scale != 0) {
            if (pv.scale != defaultScale) {
                newValue = transformScale(newValue, pv.scale, false);
            }
        }
        if (pv.base != 0) {
            if (pv.base != defaultBase) {
                newValue = transformBase(newValue, pv.base, false);
            }
        }
        if (std::any_cast<std::string>(newValue) != std::any_cast<std::string>(value)) {
            cv.value = newValue;
        }
    }


    void transformReadResult(CommandValue cv, const contracts::ResourceProperties &pv) {
        if (!isNumericValueType(cv)) {
            return;
        }
        if (isNan(cv)) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_NAN_ERROR,
                                                   "NaN error for DeviceResource " + cv.identifier);
        }
        auto value = commandValueForTransform(cv);
        auto newValue = value;
        if (pv.mask != 0l && pv.mask != defaultMask &&
            (cv.type == contracts::constants::VALUE_TYPE_INT || cv.type == contracts::constants::VALUE_TYPE_LONG)) {
            newValue = transformReadMask(newValue, pv.mask);
        }
        if (pv.shift != 0l && pv.shift != defaultShift &&
            (cv.type == contracts::constants::VALUE_TYPE_INT || cv.type == contracts::constants::VALUE_TYPE_LONG)) {
            newValue = transformReadShift(newValue, pv.shift);
        }
        if (pv.base != 0 && pv.base != defaultBase) {
            newValue = transformBase(newValue, pv.base, false);
        }
        if (pv.scale != 0 && pv.scale != defaultScale) {
            newValue = transformScale(newValue, pv.scale, false);
        }
        if (std::any_cast<std::string>(newValue) != std::any_cast<std::string>(value)) {
            cv.value = newValue;
        }
    }

    CommandValue mapCommandValue(CommandValue value, const std::map<std::string, std::string> &mappings) {
        CommandValue result;
        if (!mappings.empty()) {
            if (mappings.find(value.valueToString()) != mappings.end()) {
                auto newValue = mappings.at(value.valueToString());
                if (!newValue.empty()) {
                    result = CommandValue::newCommandValue(value.identifier,
                                                           contracts::constants::VALUE_TYPE_STRING, newValue);
                }
            }
        }
        return result;
    }

    std::optional<phecda::contracts::Event> commandValuesToEvent(
            const std::list<CommandValue> &cvs, const std::string &deviceName, const std::string &sourceName,
            bool dataTransform,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        if (cvs.empty()) {
            return std::nullopt;
        }
        auto device = phecda::sdk::cache::devices()->forName(deviceName);
        if (!device.has_value()) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_ENTITY_DOSE_NOT_EXIST,
                                                   "failed to find device " + deviceName);
        }
        bool transformsOk = true;
        long long origin = uniqueOrigin();
        std::map<std::string, std::any> tags = {};
        std::list<contracts::BaseReading> readings = {};

        for (auto cv: cvs) {
            auto dr = cache::profiles()->deviceProperty(device->productKey, cv.identifier);
            if (!dr.has_value()) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_ENTITY_DOSE_NOT_EXIST,
                                                       "failed to find DeviceResource " + cv.identifier +
                                                       " in Device " + deviceName + " for CommandValue " +
                                                       cv.toString());
            }
            if (dataTransform) {
                try {
                    transformReadResult(cv, dr.value().properties);
                } catch (contracts::CommonPhecdaException &e) {
                    if (e.kind() == contracts::error_kind::KIND_OVERFLOW_ERROR) {
                        cv = CommandValue::newCommandValue(cv.identifier,
                                                           contracts::constants::VALUE_TYPE_STRING, Overflow);
                    } else if (e.kind() == contracts::error_kind::KIND_NAN_ERROR) {
                        cv = CommandValue::newCommandValue(cv.identifier,
                                                           contracts::constants::VALUE_TYPE_STRING, NaN);
                    } else {
                        transformsOk = false;
                    }
                } catch (std::exception &e) {
                    transformsOk = false;
                }
            }
            if (!cv.tags.empty()) {
                tags.insert(cv.tags.begin(), cv.tags.end());
            }
//            auto ro = cache::profiles()->resourceOperation(device->productKey, cv.identifier);
//            if (ro.has_value()) {
//                if (!ro.value().mappings.empty()) {
//                    auto _mapCommandValue = mapCommandValue(cv, ro.value().mappings);
//                    cv = _mapCommandValue;
//                }
//            }
            auto reading = commandValueToReading(cv, deviceName, device->productKey, dr.value().properties.mediaType,
                                                 origin);
            addReadingTags(reading);
            readings.push_back(reading);
        }
        if (!transformsOk) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                   "failed to transform value for " + deviceName);
        }
        if (!readings.empty()) {
            auto event = contracts::Event::newEvent(device->productKey, device->name, sourceName);
            event.readings = readings;
            event.origin = origin;
            event.tags = tags;
            addEventTags(event);
            return event;
        }
        return std::nullopt;
    }

    contracts::BaseReading
    commandValueToReading(CommandValue cv, const std::string &deviceName, const std::string &profileName,
                          const std::string &mediaType,
                          long eventOrigin) {
        contracts::BaseReading reading;
        if (cv.type == contracts::constants::VALUE_TYPE_BINARY) {
            reading = contracts::BinaryReading::newBinaryReading(profileName, deviceName, cv.identifier,
                                                                 cv.binaryValue(), mediaType);
        } else if (cv.type == contracts::constants::VALUE_TYPE_STRUCT) {
            reading = contracts::ObjectReading::newObjectReading(profileName, deviceName, cv.identifier,
                                                                 cv.value);
        } else {
            reading = contracts::SimpleReading::newSimpleReading(profileName, deviceName, cv.identifier,
                                                                 cv.type, cv.value);
        }
        if (cv.origin > 0) {
            reading.origin = cv.origin;
        } else {
            reading.origin = eventOrigin;
        }
        return reading;
    };

}