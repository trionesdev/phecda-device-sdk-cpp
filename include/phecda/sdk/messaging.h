//
// Created by fengxiaotx on 2024/7/1.
//

#ifndef PHECDA_DEVICE_SDK_MESSAGING_H
#define PHECDA_DEVICE_SDK_MESSAGING_H


#include <phecda/bootstrap/bootstrap.h>

namespace phecda::sdk {
    bool messagingBootstrapHandler(const bootstrap::BootstrapHandlerArgs &args);

    class MessagingClient {
    public:
        virtual void connect() = 0;

        virtual void publish(std::string topic, std::vector<std::byte> message) = 0;

        virtual void subscribeDefault() = 0;

        virtual void
        subscribe(std::string topic, std::function<void(std::string, std::vector<std::byte>)> callback) = 0;
    };

} // sdk
// phecda

#endif //PHECDA_DEVICE_SDK_MESSAGING_H
