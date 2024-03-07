#include <iostream>
#include <ostream>

#include "src/library.h"
#include "src/protocol_driver.h"
// #include "include/protocol_driver.h"
//
// Created by Bane Shi on 2024/3/6.
//
int main() {
    std::cout << "Hello, World!2" << std::endl;
    auto* p = new phecda::ProtocolDriver() ;
    const std::string ss="df";
    bootstrap(ss);
    return 0;
}