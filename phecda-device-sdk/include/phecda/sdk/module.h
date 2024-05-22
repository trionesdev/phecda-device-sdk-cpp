//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_MODULE_H
#define PHECDA_DEVICE_MODULE_H

#include <string>
#include <map>
#include <any>
#include <list>

namespace phecda{

    struct CommandRequest{
        std::string deviceResourceName;
        std::map<std::string, std::any> attributes;
        std::string type;
    };

    struct CommandValue{
        std::string deviceResourceName;
        std::string  type;
        std::any value;
        long origin;
        std::map<std::string,std::any> tags;
    };

    struct AsyncValues{
        std::string deviceName;
        std::string sourceName;
        std::list<CommandRequest> commandValues;
    };

}
#endif //PHECDA_DEVICE_MODULE_H
