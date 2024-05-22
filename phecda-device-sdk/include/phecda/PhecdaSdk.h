//
// Created by fengxiaotx on 2024/5/21.
//

#ifndef PHECDA_DEVICE_SDK_APP_PHECDASDK_H
#define PHECDA_DEVICE_SDK_APP_PHECDASDK_H

#include <string>
#include <phecda/ProtocolDriver.h>

namespace phecda {

    void bootstrap(std::string args[], const std::string &serviceKey, const std::string &serviceVersion,
                   ProtocolDriver *protocolDriver);
}
#endif //PHECDA_DEVICE_SDK_APP_PHECDASDK_H
