//
// Created by fengxiaotx on 2024/5/22.
//
#include <phecda/sdk/AutoEventManager.h>
#include <map>
#include <any>
#include "phecda/bootstrap/di.h"
#include "phecda/contracts/model.h"

namespace phecda {


    class Executor {
    private:
        std::string deviceName;
        std::string sourceName;
        bool onChange = false;
        std::map<std::string, std::any> lastReadings;
        bool stopFlag = false;
    public:
        static Executor newExecutor() {
            return {};
        };

        void run(bootstrap::Container *dic) {
            Executor executor = *this;

        };

        void stop() {

        }

    };

    class DeviceAutoEventManager : public AutoEventManager {
    private:
        std::map<std::string, std::list<Executor>> executorMap = {};
        bootstrap::Container *dic{};

        static bool bootstrapHandler(BootstrapHandlerArgs args) {
            DeviceAutoEventManager manager;
            manager.executorMap = {};
            manager.dic = args.dic;
            args.dic->update({manager});
            return true;
        }

    public:
        std::list<Executor> triggerExecutors(std::string deviceName, std::list<AutoEvent> autoEvents, Container *dic) {
            auto executors = std::list<Executor>();
            if (!autoEvents.empty()) {
                for (auto autoEvent: autoEvents) {

                }
            }
            return executors;
        }

        void startAutoEvents() override {

        }

        void restartForDevice(std::string name) override {
            stopForDevice(name);
        }

        void stopForDevice(std::string name) override {
            auto executors = executorMap.find(name);
            if (executors != executorMap.end()) {
                for (auto executor: executors->second) {
                    executor.stop();
                }
                executorMap.erase(name);
            }
        }
    };

}