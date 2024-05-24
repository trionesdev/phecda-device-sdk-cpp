//
// Created by fengxiaotx on 2024/5/24.
//
#include <iostream>
#include <list>
#include <string>

#include "phecda/bootstrap/flags.h"
//#include "../environement/Variables.h"

using namespace std;
namespace phecda::bootstrap {
    CommonArgs* CommonArgs::withUsage(std::string const &additionalUsage) {
        auto *argsObj = new CommonArgs();
        argsObj->defaultConfigFile = additionalUsage;
        return argsObj;
    }

    void CommonArgs::helpCallback() {
//        std::string help = (boost::format("Usage: %1% [options]\n"
//                                          "Server Options:\n"
//                                          "    -cp, --configProvider        Indicates to use Configuration Provider service at specified URL.\n"
//                                          "                                 URL Format: {type}.{protocol}://{host}:{port} ex: consul.http://localhost:8500\n"
//                                          "    -cc, --commonConfig          Takes the location where the common configuration is loaded from when\n"
//                                          "                                 not using the Configuration Provider\n"
//                                          "    -o, --overwrite              Overwrite configuration in provider with local configuration\n"
//                                          "                                 *** Use with cation *** Use will clobber existing settings in provider,\n"
//                                          "                                 problematic if those settings were edited by hand intentionally\n"
//                                          "    -cf, --configFile <name>     Indicates name of the local configuration file. Defaults to configuration.yaml\n"
//                                          "    -p, --profile <name>         Indicate configuration profile other than default\n"
//                                          "    -cd, --configDir             Specify local configuration directory\n"
//                                          "    -r, --registry               Indicates service should use Registry.\n"
//                                          "    -rsh, \n"
//                                          "     --remoteServiceHosts \n"
//                                          "          <host names>           Indicates that the service is running remote from the core EdgeX services and\n"
//                                          "                                 to use the listed host names to connect remotely. <host names> contains 3 comma seperated host names seperated by ','.\n"
//                                          "                                 1st is the local system host name, 2nd is the remote system host name and 3rd is the WebServer bind host name\n"
//                                          "                                 example: -rsh=192.0.1.20,192.0.1.5,localhost\n"
//                                          "    -d, --dev                    Indicates service to run in developer mode which causes Host configuration values to be overridden.\n"
//                                          "                                 with `localhost`. This is so that it will run with other services running in Docker (aka hybrid mode)\n"
//                                          "%2%\n"
//                                          "Common Options:\n"
//                                          "    -h, --help                   Show this message\n") %
//                            "22" % additionalUsage).str();
//        std::cout << help << std::endl;
    }

    bool CommonArgs::overwriteConfig() {
        return false;
    }

    string CommonArgs::profile() {
        return std::string();
    }

    string CommonArgs::configDirectory() {
        return std::string();
    }

    string CommonArgs::configFileName() {
        return std::string();
    }

    string CommonArgs::commonConfig() {
        return std::string();
    }

    void CommonArgs::parse(list<string> arguments) {

    }


}