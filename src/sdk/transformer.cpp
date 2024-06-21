//
// Created by fengxiaotx on 2024/6/18.
//
#include "phecda/sdk/transformer.h"
#include <iostream>
#include <chrono>
#include "phecda/contracts/errors.h"
#include "phecda/contracts/constants.h"
#include <phecda/sdk/cache.h>
#include <phecda/contracts/model.h>
#include <phecda/sdk/common_utils.h>

namespace phecda::sdk::transformer {

    long uniqueOrigin() {
        auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
        );
        return currentTime.count();
    }

    void transformWriteParameter(const CommandValue &cv, const contracts::ResourceProperties &pv) {
        std::cout << "sss" << std::endl;
    }

    void validateWriteMaximum(std::any value, double maximum) {
        std::cout << "sss" << std::endl;
    };

    void transformReadResult(CommandValue cv, contracts::ResourceProperties pv) {}

    CommandValue mapCommandValue(CommandValue value, std::map<std::string, std::string> mappings) {
        return value;
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
        long origin = uniqueOrigin();
        std::map<std::string, std::any> tags = {};
        std::list<contracts::BaseReading> readings = {};

        for (auto cv: cvs) {
            auto dr = cache::profiles()->deviceResource(device->profileName, cv.deviceResourceName);
            if (!dr.has_value()) {
                throw contracts::CommonPhecdaException(contracts::error_kind::KIND_ENTITY_DOSE_NOT_EXIST,
                                                       "failed to find DeviceResource " + cv.deviceResourceName +
                                                       " in Device " + deviceName + " for CommandValue " +
                                                       cv.toString());
            }
            if (dataTransform) {
                try {
                    transformReadResult(cv, dr.value().properties);
                } catch (contracts::CommonPhecdaException &e) {
                    if (e.kind() == contracts::error_kind::KIND_OVERFLOW_ERROR) {
                        cv = CommandValue::newCommandValue(cv.deviceResourceName,
                                                           contracts::constants::VALUE_TYPE_STRING, Overflow);
                    } else if (e.kind() == contracts::error_kind::KIND_NAN_ERROR) {
                        cv = CommandValue::newCommandValue(cv.deviceResourceName,
                                                           contracts::constants::VALUE_TYPE_STRING, NaN);
                    } else {
                        transformsOk = false;
                    }
                }
            }
            if (!cv.tags.empty()) {
                tags.insert(cv.tags.begin(), cv.tags.end());
            }
            auto ro = cache::profiles()->resourceOperation(device->profileName, cv.deviceResourceName);
            if (ro.has_value()) {
                if (!ro.value().mappings.empty()) {
                    auto _mapCommandValue = mapCommandValue(cv, ro.value().mappings);
                    cv = _mapCommandValue;
                }
            }
            auto reading = commandValueToReading(cv, deviceName, device->profileName, dr.value().properties.mediaType,
                                                 origin);
            addReadingTags(reading);
            readings.push_back(reading);
        }
        if (!transformsOk) {
            throw contracts::CommonPhecdaException(contracts::error_kind::KIND_SERVER_ERROR,
                                                   "failed to transform value for " + deviceName);
        }
        if (!readings.empty()) {
            auto event = contracts::Event::newEvent(device->profileName, device->name, sourceName);
            event.readings = readings;
            event.origin = origin;
            event.tags = tags;
            addEventTags(event);
            return event;
        }
        return std::nullopt;
    }

    contracts::BaseReading
    commandValueToReading(CommandValue cv, std::string deviceName, std::string profileName, std::string mediaType,
                          long eventOrigin) {
        return {};
    };

}