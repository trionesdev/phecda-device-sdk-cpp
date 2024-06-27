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

namespace phecda::sdk {

    struct CommandRequest {
        std::string deviceResourceName;
        std::map<std::string, std::any> attributes;
        std::string type;
    };

    struct CommandValue {
        std::string deviceResourceName;
        std::string type;
        std::any value;
        long origin = 0;
        std::map<std::string, std::any> tags;

        static CommandValue
        newCommandValue(const std::string &deviceResourceName, const std::string &valueType, const std::any &value);
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
        std::string sourceName;
        std::list<CommandRequest> commandValues;
    };

}
#endif //PHECDA_DEVICE_MODULE_H
