//
// Created by fengxiaotx on 2024/5/27.
//
#include <phecda/sdk/auto_event.h>
#include <phecda/sdk/container.h>

namespace phecda::sdk {


    Executor Executor::newExecutor() {
        return Executor();
    }

    void Executor::run(DiContainer *dic) {

    }

    void Executor::stop() {

    }

    bool AutoEventManager::bootstrapHandler(phecda::bootstrap::BootstrapHandlerArgs args) {
        auto *manager = new AutoEventManager();
        manager->executorMap = {};
        manager->dic = args.dic;
        manager->wg = args.wg;
        args.dic->update({{phecda::sdk::container::autoEventManagerName, manager}});
        return true;
    }

    std::list<Executor>
    triggerExecutors(std::string deviceName, std::list<contracts::AutoEvent> autoEvents, bootstrap::DiContainer *dic) {
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