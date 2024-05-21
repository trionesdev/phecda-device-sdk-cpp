//
// Created by fengxiaotx on 2024/5/21.
//


#ifndef PHECDA_DEVICE_PHECDA_DEVICE_SDK_H
#define PHECDA_DEVICE_PHECDA_DEVICE_SDK_H

namespace phecda {

    class ProtocolDriver {
    public:
        void initialize();
    };

    void bootstrap(std::string args[], const std::string& serviceKey, const std::string& serviceVersion, ProtocolDriver *protocolDriver);

}

#endif //PHECDA_DEVICE_PHECDA_DEVICE_SDK_H
