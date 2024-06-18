//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_MODEL_H
#define PHECDA_DEVICE_MODEL_H

#include <string>
#include <map>
#include <any>
#include <list>
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
        AdminState adminState;
        OperatingState operatingState;
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
        AdminState adminState;
    };

    struct Event{

    };

}

#endif //PHECDA_DEVICE_MODEL_H
