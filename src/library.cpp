#include "library.h"

#include <iostream>


void bootstrap(const std::string& serviceKey,phecda::ProtocolDriver *driver)
{
    std::cout << "Hello, World!"<< serviceKey << std::endl;
}
