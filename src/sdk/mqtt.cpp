//
// Created by fengxiaotx on 2024/7/1.
//

#include "phecda/sdk/mqtt.h"
#include <phecda/log/log.h>


namespace phecda::sdk {
    static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sdk/messaging"));

    class MqttCallback : public virtual mqtt::callback {
        void connected(const std::string &cause) override {
            std::cout << "\tCause: " << cause << std::endl;
            LOG_INFO(logger, cause);
        }

        void connection_lost(const std::string &cause) override {
            LOG_INFO(logger, cause);

        }

        void delivery_complete(mqtt::delivery_token_ptr token) override {
            LOG_INFO(logger, "Delivery complete for token: "
                    << (token ? token->get_message_id() : -1)
                    << std::endl);

        }
    };

    std::shared_ptr<MqttMessagingClient>
    MqttMessagingClient::newMqttClient(const MqttInfo &mqttInfo, const shared_ptr<bootstrap::DiContainer> &dic) {
        std::string serverUri = mqttInfo.protocol + "://" + mqttInfo.host + ":" + std::to_string(mqttInfo.port);
        auto client = std::make_shared<mqtt::async_client>(serverUri, mqttInfo.clientId);

        mqtt::connect_options connOpts;
        connOpts.set_user_name(mqttInfo.username);
        connOpts.set_password(mqttInfo.password);
        connOpts.set_connect_timeout(mqttInfo.connectionTimeout);
        connOpts.set_automatic_reconnect(mqttInfo.automaticReconnect);
        connOpts.set_clean_session(mqttInfo.cleanSession);
        connOpts.set_keep_alive_interval(mqttInfo.keepAliveInterval);

        auto mqttClient = std::make_shared<MqttMessagingClient>(client);
        mqttClient->_connOpts = connOpts;
        mqttClient->_topicPrefix = mqttInfo.topicPrefix;
        return mqttClient;
    }

    void MqttMessagingClient::connect() {
        MqttCallback cb;
        _mqttClient->set_callback(cb);
        try {
            _mqttClient->connect(_connOpts)->wait();
        } catch (const mqtt::exception &exc) {
            LOG_ERROR(logger, "[mqtt.cpp] mqtt connect failed" << exc.what());
        }
    }

    void MqttMessagingClient::subscribeDefault() {

    }

    void MqttMessagingClient::publish(std::string topic, std::vector<std::byte> message) {
//        mqtt::message msg("test", message.data(), message.size(), 0, false);
        auto msg = mqtt::make_message(_topicPrefix + "/" + topic,
                                      std::string(reinterpret_cast<const char *>(message.data()), message.size()));
        _mqttClient->publish(msg);
    }

    void MqttMessagingClient::subscribe(std::string topic,
                                        std::function<void(std::string, std::vector<std::byte>)> callback) {

    }

    MqttMessagingClient::~MqttMessagingClient() {
        if (_mqttClient->is_connected()) {
            _mqttClient->disconnect();
        }
    }

    void MqttMessagingClient::publish(std::string topic, string message) {
        auto msg = mqtt::make_message(_topicPrefix + "/" + topic, message);
        _mqttClient->publish(msg);
    }


} // phecda