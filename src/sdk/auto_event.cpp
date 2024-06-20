//
// Created by fengxiaotx on 2024/5/27.
//
#include <phecda/sdk/auto_event.h>
#include <phecda/sdk/container.h>
#include <phecda/sdk/cache.h>
#include <phecda/contracts/constants.h>
#include <phecda/sdk/application.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace phecda::sdk {

    bool compareReadings(std::list<contracts::BaseReading> readings){
        return true;
    }

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

    std::optional<contracts::Event>
    Executor::readResource(const Executor *executor, std::shared_ptr<bootstrap::DiContainer> dic) {
        std::map<std::string, std::string> vars = {};
        vars[phecda::contracts::constants::NAME] = executor->_deviceName;
        vars[phecda::contracts::constants::COMMAND] = executor->_sourceName;
        return phecda::sdk::application::getCommand(executor->_deviceName, executor->_sourceName, "", false, dic);
    }

    void Executor::run(const std::shared_ptr<bootstrap::DiContainer> &dic) {
        std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::seconds>(_duration);
        function<void(void)> fun = [this, dic]() {
            std::optional<contracts::Event> event;
            try {
                event = readResource(this, dic);
            } catch (std::exception &e) {
            }
            if(event.has_value()){
                if(_onChange){
                    if(!compareReadings(event.value().readings)){
                        //TODO
                    }
                }
                auto correlationId = boost::uuids::to_string(boost::uuids::random_generator()());
            }

        };
        _timer = std::make_shared<phecda::util::Timer>();
        _timer->schedule(fun, milliseconds.count(), milliseconds.count());
    }

    void Executor::stop() {
        _stop = true;
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
                     std::shared_ptr<bootstrap::DiContainer> dic) {
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

    void AutoEventManager::stopForDevice(const std::string &name) {
        if (executorMap.find(name) != executorMap.end()) {
            for (const auto &executor: executorMap[name]) {
                executor->stop();
            }
            executorMap.erase(name);
        }
    }

    void AutoEventManager::startAutoEvents() {
        auto devices = phecda::sdk::cache::devices()->all();
        for (const auto &device: devices) {
            if (executorMap.find(device.name) == executorMap.end()) {
                executorMap[device.name] = triggerExecutors(device.name, device.autoEvents, dic);
            }
        }
    }

    void AutoEventManager::restartForDevice(const std::string &name) {
        stopForDevice(name);
        auto device = phecda::sdk::cache::devices()->forName(name);
        if (device.has_value()) {
            executorMap[name] = triggerExecutors(name, device.value().autoEvents, dic);
        }
    }


}