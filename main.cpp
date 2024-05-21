#include <iostream>
#include <ostream>
#include <algorithm>

#include "phecda-device-sdk/src/phecda_device_sdk.h"
//
// Created by Bane Shi on 2024/3/6.
//
int main(int argc, char* argv[]) {

    std::string args[argc];
    std::cout << "Hello, World!2" << std::endl;
    auto* p = new phecda::ProtocolDriver() ;
    phecda::bootstrap(args,"device-virtual","0.0.1",p);
    return 0;
}