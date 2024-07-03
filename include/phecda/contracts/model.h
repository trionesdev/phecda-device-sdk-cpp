//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_MODEL_H
#define PHECDA_DEVICE_MODEL_H

#include <string>
#include <map>
#include <any>
#include <list>
#include <vector>
#include "enums.h"

namespace phecda::contracts {

    struct DBTimestamp {
        long created;
        long modified;
    };

    struct AutoEvent {
        std::string interval;
        bool onChange;
        std::string sourceName;
    };

    struct Device {
        std::string id;
        std::string name;
        std::string description;
        std::string adminState;
        std::string operatingState;
        std::map<std::string, std::map<std::string, std::any>> protocols;
        std::list<std::string> labels;
        std::any location;
        std::string serviceName;
        std::string profileName;
        std::list<AutoEvent> autoEvents;
        std::map<std::string, std::any> tags;
        std::map<std::string, std::any> properties;
    };

    struct ResourceProperties {
        std::string valueType;
        std::string readWrite;
        std::string units;
        double minimum;
        double maximum;
        std::string defaultValue;
        long mask;
        long shift;
        double scale;
        double offset;
        double base;
        std::string assertion;
        std::string mediaType;
        std::map<std::string, std::any> optional;
    };

    struct DeviceResource {
        std::string name;
        std::string description;
        bool isHidden;
        ResourceProperties properties;
        std::map<std::string, std::any> attributes;
        std::map<std::string, std::any> tags;
    };

    struct ResourceOperation {
        std::string deviceResource;
        std::string defaultValue;
        std::map<std::string, std::string> mappings;
    };

    struct DeviceCommand {
        std::string name;
        bool isHidden;
        std::string readWrite;
        std::list<ResourceOperation> resourceOperations;
        std::map<std::string, std::any> tags;
    };

    struct DeviceProfile : DBTimestamp {
        std::string id;
        std::string name;
        std::string description;
        std::string manufacturer;
        std::string model;
        std::list<std::string> labels;
        std::list<DeviceResource> deviceResources;
        std::list<DeviceCommand> deviceCommands;
    };

    struct DeviceService : DBTimestamp {
        std::string id;
        std::string name;
        std::string description;
        std::list<std::string> labels;
        std::string adminState;
    };

    struct BaseReading {
        std::string id;
        long long origin;
        std::string deviceName;
        std::string resourceName;
        std::string profileName;
        std::string valueType;
        std::string utils;
        std::map<std::string, std::any> tags;
        std::vector<std::byte> binaryValue;
        std::string mediaType;
        std::any objectValue;
        std::string value;

        static BaseReading
        newBaseReading(const std::string &profileName, const std::string &deviceName, const std::string &resourceName,
                       const std::string &valueType);

    };

    struct BinaryReading : BaseReading {
        std::byte binaryValue;
        std::string mediaType;

        static BaseReading
        newBinaryReading(const std::string &profileName, const std::string &deviceName, const std::string &resourceName,
                         const std::vector<std::byte> &binaryValue, const std::string &mediaType);
    };

    struct ObjectReading : BaseReading {
        std::any objectValue;

        static BaseReading
        newObjectReading(const std::string &profileName, const std::string &deviceName, const std::string &resourceName,
                         const std::any &objectValue);
    };

    struct SimpleReading : BaseReading {
        std::string value;

        static BaseReading
        newSimpleReading(const std::string &profileName, const std::string &deviceName, const std::string &resourceName,
                         const std::string &valueType, std::any &value);
    };

    struct Event {
        std::string id;
        std::string deviceName;
        std::string profileName;
        std::string sourceName;
        long long origin{};
        std::list<BaseReading> readings;
        std::map<std::string, std::any> tags;

        static Event newEvent(std::string profileName, std::string deviceName, std::string sourceName);

    };

}

#endif //PHECDA_DEVICE_MODEL_H
