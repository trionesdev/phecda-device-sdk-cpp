//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_SDK_FLAGS_H
#define PHECDA_DEVICE_SDK_FLAGS_H
#include <list>
#include <string>

using namespace std;


namespace phecda::bootstrap
{
    class CommonArgs
    {
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
        static CommonArgs* withUsage(std::string const& additionalUsage);

        void helpCallback();

        bool overwriteConfig();

        string profile();

        string configDirectory();

        string configFileName();

        string commonConfig();

        void parse(std::list<string> arguments);
    };
}


#endif //PHECDA_DEVICE_SDK_FLAGS_H
