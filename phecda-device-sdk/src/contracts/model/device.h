//
// Created by fengxiaotx on 2024/5/21.
//

#ifndef PHECDA_DEVICE_DEVICE_H
#define PHECDA_DEVICE_DEVICE_H

#include <string>
#include <map>
#include <list>
#include <any>
#include "enums.h"
#include "auto_event.h"

namespace phecda {

    class Device {
    public:
        std::string id;
        std::string name;
        std::string description;
        phecda::AdminState adminState;
        phecda::OperatingState operationalState;
        std::map<std::string, std::map<std::string, std::any >> protocols;
        std::list<std::string> labels;
        std::any location;
        std::string serviceName;
        std::string profileName;
        std::list<phecda::AutoEvent> autoEvents;
        std::map<std::string, std::any> tags;
        std::map<std::string, std::any> properties;
    };

} // phecda

#endif //PHECDA_DEVICE_DEVICE_H
