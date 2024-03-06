#ifndef PHECDA_DEVICE_SDK_CPP_LIBRARY_H
#define PHECDA_DEVICE_SDK_CPP_LIBRARY_H

#include <string>

#include "protocol_driver.h"


void bootstrap(const std::string& serviceKey,phecda::ProtocolDriver *driver);

#endif //PHECDA_DEVICE_SDK_CPP_LIBRARY_H
