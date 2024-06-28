#include <iostream>
#include <ostream>
#include "phecda/sdk/PhecdaSdk.h"


//
// Created by Bane Shi on 2024/3/6.
//

int main(int argc, char* argv[]) {

    std::string args[2] = {"1","2"};
    std::cout << "Hello, World!2" << std::endl;
    auto *driver = new phecda::sdk::ProtocolDriver();
    phecda::sdk::bootstrap(args,"device-virtual","0.0.1",driver);
    return 0;
}