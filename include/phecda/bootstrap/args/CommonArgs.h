//
// Created by fengxiaotx on 2024/5/24.
//

#ifndef PHECDA_DEVICE_SDK_COMMONARGS_H
#define PHECDA_DEVICE_SDK_COMMONARGS_H

#include <string>
#include <utility>

using namespace std;

namespace phecda {
    class CommonArgs {
    public:
        std::string defaultConfigFile = "configuration.yaml";
//    private:
//        string additionalUsage;
//        bool _overwriteConfig = false;
//        bool devMode = false;
//        string _commonConfig = "";
//        string _profile = "";
//        string _configDir = "";
//        string _configFileName = "";
    public:
        static CommonArgs withUsage(std::string const &additionalUsage){
            return {};
        };

        void helpCallback();

        bool overwriteConfig();

        string profile();

        string configDirectory();

        string configFileName();

        string commonConfig();

        void parse(list <string> arguments);
    };


}
#endif //PHECDA_DEVICE_SDK_COMMONARGS_H
