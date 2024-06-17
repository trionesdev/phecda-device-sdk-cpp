//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_AUTOEVENTMANAGER_H
#define PHECDA_DEVICE_AUTOEVENTMANAGER_H

#include "phecda/bootstrap/di-container.h"
#include "phecda/bootstrap/bootstrap.h"
#include <phecda/contracts/model.h>
#include <phecda/util/DurationUtils.h>

using namespace phecda::bootstrap;

namespace phecda::sdk {
    class Executor {
    private:
        std::string _deviceName;
        std::string _sourceName;
        bool _onChange = false;
        std::map<std::string, std::any> _lastReadings;
        std::chrono::duration<int> _duration;
        bool _stop = false;
    public:
        static std::shared_ptr<Executor> newExecutor(const std::string& deviceName,const contracts::AutoEvent& autoEvent);

        void run(DiContainer *dic);

        void stop();
    };


    class AutoEventManager {
    private:
        std::map<std::string, std::list<Executor>> executorMap = {};
        std::shared_ptr<contracts::WaitGroup> wg;
        bootstrap::DiContainer *dic;
    public:
        static bool bootstrapHandler(BootstrapHandlerArgs args);

        void startAutoEvents();

        void restartForDevice(std::string name);

        void stopForDevice(const std::string& deviceName);
    };

}
#endif //PHECDA_DEVICE_AUTOEVENTMANAGER_H
