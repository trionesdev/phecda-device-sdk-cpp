//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_AUTOEVENTMANAGER_H
#define PHECDA_DEVICE_AUTOEVENTMANAGER_H

#include "phecda/bootstrap/di.h"
#include "phecda/bootstrap/bootstrap.h"
#include <phecda/contracts/model.h>

using namespace phecda::bootstrap;

namespace phecda::sdk {
    class Executor {
    private:
        std::string deviceName;
        std::string sourceName;
        bool onChange = false;
        std::map<std::string, std::any> lastReadings;
        bool _stop = false;
    public:
        static Executor newExecutor();

        void run(Container *dic);

        void stop();
    };




    class AutoEventManager {
    private:
        std::map<std::string, std::list<Executor>> executorMap = {};
        bootstrap::Container *dic;
    public:
        static bool bootstrapHandler(BootstrapHandlerArgs args);
         void startAutoEvents();

         void restartForDevice(std::string name);

         void stopForDevice(std::string deviceName);
    };

}
#endif //PHECDA_DEVICE_AUTOEVENTMANAGER_H
