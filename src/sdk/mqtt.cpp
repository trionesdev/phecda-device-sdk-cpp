//
// Created by fengxiaotx on 2024/7/1.
//

#include "phecda/sdk/mqtt.h"
#include <phecda/sdk/cache.h>
#include <phecda/log/log.h>


namespace phecda::sdk {
    static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sdk/mqtt"));

    class callback : public virtual mqtt::callback {
    public:
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

    class action_listener : public virtual mqtt::iaction_listener
    {
        std::function<void(std::string, std::vector<std::byte>)> _callback;

        void on_failure(const mqtt::token& tok) override {

        }

        void on_success(const mqtt::token& tok) override {

        }

    public:
        explicit action_listener(const std::function<void(std::string, std::vector<std::byte>)>& callback) : _callback(callback) {}
    };


    std::shared_ptr<MqttMessagingClient>
    MqttMessagingClient::newMqttClient(const MqttInfo &mqttInfo, const shared_ptr<bootstrap::DiContainer> &dic) {
        std::string serverUri = mqttInfo.protocol + "://" + mqttInfo.host + ":" + std::to_string(mqttInfo.port);
        auto client = std::make_shared<mqtt::async_client>(serverUri, mqttInfo.clientId);
        client->set_connected_handler([&](const std::string &cause) {
            std::cout << "\tCause: " << cause << std::endl;
            LOG_INFO(logger, cause);
        });
        client->set_disconnected_handler([&](const mqtt::properties&, mqtt::ReasonCode) {});
        client->set_connection_lost_handler([&](const std::string &cause) {
            LOG_INFO(logger, cause);
        });
        client->set_message_callback([&](mqtt::const_message_ptr msg) {
            LOG_INFO(logger, "Delivery complete for token: "
                    << (msg ? 1 : -1)
                    << std::endl);
        });

        auto connOptionsBuilder = mqtt::connect_options_builder().user_name(mqttInfo.username)
                .password(mqttInfo.password).clean_session(mqttInfo.cleanSession).automatic_reconnect(mqttInfo.automaticReconnect)
                .connect_timeout(std::chrono::seconds(mqttInfo.connectionTimeout))
                .keep_alive_interval(std::chrono::seconds(mqttInfo.keepAliveInterval));

        auto connOptions = std::make_shared<mqtt::connect_options>();
        connOptions->set_user_name(mqttInfo.username);
        connOptions->set_password(mqttInfo.password);
        connOptions->set_clean_session(mqttInfo.cleanSession);
        connOptions->set_automatic_reconnect(mqttInfo.automaticReconnect);
        connOptions->set_connect_timeout(std::chrono::seconds(mqttInfo.connectionTimeout));
        connOptions->set_keep_alive_interval(std::chrono::seconds(mqttInfo.keepAliveInterval));

        auto mqttClient = std::make_shared<MqttMessagingClient>();
        mqttClient->_mqttClient = client;
        mqttClient->_connOpts = connOptions;
        mqttClient->_topicPrefix = mqttInfo.topicPrefix;
        return mqttClient;
    }

    void MqttMessagingClient::connect() {
        try {
//            auto cb = std::make_shared<callback>();
//            _mqttClient->set_callback(*cb);
            _mqttClient->connect(*_connOpts)->wait();
        } catch (const mqtt::exception &exc) {
            LOG_ERROR(logger, "[mqtt.cpp] mqtt connect failed" << exc.what());
        }
    }

    void MqttMessagingClient::subscribeDefault() {
       auto profiles = phecda::sdk::cache::profiles()->all();
    }

    void MqttMessagingClient::publish(std::string topic, std::vector<std::byte> message) {
        auto msg = mqtt::make_message(_topicPrefix + "/" + topic,
                                      std::string(reinterpret_cast<const char *>(message.data()), message.size()));
        try {
            _mqttClient->publish(msg);
        }catch (const mqtt::exception &exc) {
            LOG_ERROR(logger, "[mqtt.cpp] mqtt publish failed" << exc.what());
        }
    }

    void MqttMessagingClient::subscribe(std::string topic,
                                        std::function<void(std::string, std::vector<std::byte>)> callback) {
//        mqtt::iaction_listener action_listener2 = action_listener("ss");

//        action_listener action_listener("ss");
        _mqttClient->subscribe("ddd",0);
    }

    MqttMessagingClient::~MqttMessagingClient() {
        if (_mqttClient->is_connected()) {
            _mqttClient->disconnect();
        }
    }

    void MqttMessagingClient::publish(std::string topic, string message) {
        auto msg = mqtt::make_message(_topicPrefix + "/" + topic, message);
        try {
            _mqttClient->publish(msg);
        }catch (const mqtt::exception &exc) {
            LOG_ERROR(logger, "[mqtt.cpp] mqtt publish failed" << exc.what());
        }
    }


} // phecda