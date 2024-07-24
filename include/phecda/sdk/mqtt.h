//
// Created by fengxiaotx on 2024/7/1.
//

#ifndef PHECDA_DEVICE_SDK_MQTT_H
#define PHECDA_DEVICE_SDK_MQTT_H

#include <phecda/sdk/messaging.h>
#include <phecda/sdk/config.h>
#include <mqtt/async_client.h>

#include <utility>

namespace phecda::sdk {


    class MqttMessagingClient : public virtual MessagingClient {
    private:
        std::shared_ptr<mqtt::async_client> _mqttClient;
        mqtt::connect_options _connOpts;
        std::string _topicPrefix = "phecda";
    public:
        explicit MqttMessagingClient() : _mqttClient(), _connOpts(), _topicPrefix("phecda") {};

        static std::shared_ptr<MqttMessagingClient>
        newMqttClient(const MqttInfo &mqtt, const std::shared_ptr<bootstrap::DiContainer> &dic);

        void connect() override;

        void subscribeDefault() override;

        void publish(std::string topic, std::vector<std::byte> message) override;

        void publish(std::string topic, string message) override;

        void subscribe(std::string topic, std::function<void(std::string, std::vector<std::byte>)> callback) override;

        ~MqttMessagingClient();
    };

} // sdk
// phecda

#endif //PHECDA_DEVICE_SDK_MQTT_H
