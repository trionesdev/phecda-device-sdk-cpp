//
// Created by fengxiaotx on 2024/5/27.
//
#include <phecda/sdk/auto_event.h>
#include <phecda/contracts/model.h>

namespace phecda::sdk {


    Executor Executor::newExecutor() {
        return Executor();
    }

    void Executor::run(Container *dic) {

    }

    void Executor::stop() {

    }

    bool AutoEventManager::bootstrapHandler(phecda::bootstrap::BootstrapHandlerArgs args) {
        AutoEventManager manager;
        manager.executorMap = {};
        manager.dic = args.dic;
//        args.dic->update({manager});
        return true;
    }

    std::list<Executor>
    triggerExecutors(std::string deviceName, std::list<contracts::AutoEvent> autoEvents, bootstrap::Container *dic) {
        auto executors = std::list<Executor>();
        if (!autoEvents.empty()) {
            for (auto autoEvent: autoEvents) {

            }
        }
        return executors;
    }

    void AutoEventManager::stopForDevice(std::string name) {
        auto executors = executorMap.find(name);
        if (executors != executorMap.end()) {
            for (auto executor: executors->second) {
                executor.stop();
            }
            executorMap.erase(name);
        }
    }

    void AutoEventManager::startAutoEvents() {

    }

    void AutoEventManager::restartForDevice(std::string name) {

    }


}