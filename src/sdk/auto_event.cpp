//
// Created by fengxiaotx on 2024/5/27.
//
#include <phecda/sdk/auto_event.h>
#include <phecda/sdk/container.h>

namespace phecda::sdk {


    std::shared_ptr<Executor>
    Executor::newExecutor(const std::string &deviceName, const contracts::AutoEvent &autoEvent) {
        auto duration = phecda::util::DurationUtils::parse(autoEvent.interval);
        auto executor = std::make_shared<Executor>();
        executor->_deviceName = deviceName;
        executor->_sourceName = autoEvent.sourceName;
        executor->_onChange = autoEvent.onChange;
        executor->_duration = duration;
        executor->_stop = false;
        return executor;
    }

    void Executor::run(DiContainer *dic) {

    }

    void Executor::stop() {

    }

    bool AutoEventManager::bootstrapHandler(phecda::bootstrap::BootstrapHandlerArgs args) {
        auto manager = make_shared<AutoEventManager>();
        manager->executorMap = {};
        manager->dic = args.dic;
        manager->wg = args.wg;
        args.dic->update({{phecda::sdk::container::autoEventManagerName, manager}});
        return true;
    }

    std::list<std::shared_ptr<Executor>>
    triggerExecutors(const std::string &deviceName, const std::list<contracts::AutoEvent> &autoEvents,
                     bootstrap::DiContainer *dic) {
        auto executors = std::list<std::shared_ptr<Executor>>();
        if (!autoEvents.empty()) {
            for (const auto &autoEvent: autoEvents) {
                try {
                    auto executor = Executor::newExecutor(deviceName, autoEvent);
                    executors.push_back(executor);
                    executor->run(dic);
                } catch (std::exception &e) {
                    //TODO log
                    continue;
                }
            }
        }
        return executors;
    }

    void AutoEventManager::stopForDevice(const std::string& name) {
        if (executorMap.find(name) != executorMap.end()) {
            for (auto executor: executorMap[name]) {
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