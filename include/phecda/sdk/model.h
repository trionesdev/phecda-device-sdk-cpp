//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_MODULE_H
#define PHECDA_DEVICE_MODULE_H

#include <string>
#include <map>
#include <any>
#include <list>
#include <vector>
#include <phecda/contracts/model.h>

namespace phecda::sdk {

    struct CommandRequest {
        std::string identifier;
        std::map<std::string, std::any> attributes;
        std::string type;
    };

    struct CommandValue {
        std::string identifier;
        std::string type;
        std::any value;
        long origin = 0;
        std::map<std::string, std::any> tags;

        static CommandValue
        newCommandValue(const std::string &identifier, const std::string &valueType, const std::any &value);

        std::string toString();

        std::string valueToString();

        int intValue();

        long longValue();

        float floatValue();

        double doubleValue();

        std::vector<std::byte> binaryValue();

    };

    struct AsyncValues {
        std::string deviceName;
        std::string identifier;
        std::list<CommandRequest> commandValues;
    };


    struct Reading {
        std::string identifier;
        std::string valueType;
        std::string utils;
        std::vector<std::byte> binaryValue;
        std::string mediaType;
        std::any objectValue;
        std::string value;
        long long ts;

        static Reading fromBaseReading(const contracts::BaseReading &baseReading);

        static std::list<Reading> fromBaseReadings(const std::list<contracts::BaseReading> &baseReadings);

        static std::map<std::string, Reading>
        fromBaseReadingsToMap(const std::list<contracts::BaseReading> &baseReadings);
    };

    struct PhecdaEvent {
        std::string version;
        std::string id;
        std::string type;
        std::string deviceName;
        std::string productKey;
        std::string identifier;
        long long ts;
        std::map<std::string, Reading> readings;
        std::map<std::string, std::any> tags;

        static PhecdaEvent newPhecdaEvent(const contracts::Event &event);

        std::string toJsonString();
    };
}
#endif //PHECDA_DEVICE_MODULE_H
