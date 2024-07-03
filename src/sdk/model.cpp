//
// Created by fengxiaotx on 2024/6/27.
//
#include <phecda/sdk/model.h>
#include <phecda/contracts/errors.h>
#include <phecda/contracts/constants.h>
#include <numeric>
#include <nlohmann/json.hpp>

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


    Reading Reading::fromBaseReading(const contracts::BaseReading &baseReading) {
        Reading reading;
        reading.identifier = baseReading.resourceName;
        reading.valueType = baseReading.valueType;
        reading.utils = baseReading.utils;
        reading.binaryValue = baseReading.binaryValue;
        reading.mediaType = baseReading.mediaType;
        reading.objectValue = baseReading.objectValue;
        reading.value = baseReading.value;
        reading.ts = baseReading.origin;
        return reading;
    }

    std::list<Reading> Reading::fromBaseReadings(const std::list<contracts::BaseReading> &baseReadings) {
        std::list<Reading> readings;
        for (auto &baseReading: baseReadings) {
            readings.push_back(fromBaseReading(baseReading));
        }
        return readings;
    }

    std::map<std::string, Reading>
    Reading::fromBaseReadingsToMap(const std::list<contracts::BaseReading> &baseReadings) {
        auto readings = fromBaseReadings(baseReadings);
        return std::accumulate(readings.begin(), readings.end(), std::map<std::string, Reading>(),
                               [](std::map<std::string, Reading> map, const Reading &reading) {
                                   map[reading.identifier] = reading;
                                   return map;
                               });
    }

    PhecdaEvent PhecdaEvent::newPhecdaEvent(const contracts::Event &event) {
        std::map<std::string, Reading> readingsMap = Reading::fromBaseReadingsToMap(event.readings);
        PhecdaEvent phecdaEvent;
        phecdaEvent.id = event.id;
        phecdaEvent.deviceName = event.deviceName;
        phecdaEvent.productKey = event.profileName;
        phecdaEvent.sourceName = event.sourceName;
        phecdaEvent.ts = event.origin;
        phecdaEvent.readings = readingsMap;
        phecdaEvent.tags = event.tags;
        return phecdaEvent;
    }

    std::string PhecdaEvent::toJsonString() {
        nlohmann::json json;
        json["id"] = id;
        json["deviceName"] = deviceName;
        json["productKey"] = productKey;
        json["sourceName"] = sourceName;
        json["ts"] = ts;

        for (auto &reading: readings) {
            nlohmann::json objectValue;
            nlohmann::json readingJson;
            readingJson["identifier"] = reading.second.identifier;
            readingJson["valueType"] = reading.second.valueType;
            readingJson["utils"] = reading.second.utils;
            readingJson["objectValue"] = objectValue;
            readingJson["mediaType"] = reading.second.mediaType;
            readingJson["value"] = reading.second.value;
            readingJson["ts"] = reading.second.ts;

            json["readings"][reading.first] = readingJson;
        }

        for (auto &tag: tags) {
            nlohmann::json tagValue;
            if (tag.second.has_value()) {
                if (tag.second.type() == typeid(std::string)) {
                    tagValue = std::any_cast<std::string>(tag.second);
                } else if (tag.second.type() == typeid(int)) {
                    tagValue = std::any_cast<int>(tag.second);
                } else if (tag.second.type() == typeid(long)) {
                    tagValue = std::any_cast<long>(tag.second);
                } else if (tag.second.type() == typeid(float)) {
                    tagValue = std::any_cast<float>(tag.second);
                } else if (tag.second.type() == typeid(double)) {
                    tagValue = std::any_cast<double>(tag.second);
                } else if (tag.second.type() == typeid(bool)) {
                    tagValue = std::any_cast<bool>(tag.second);
                } else if (tag.second.type() == typeid(std::vector<std::byte>)) {
                    tagValue = std::any_cast<std::vector<std::byte>>(tag.second);
                }
                json["tags"][tag.first] = tagValue;
            }
        }

        return json.dump();
    }
}