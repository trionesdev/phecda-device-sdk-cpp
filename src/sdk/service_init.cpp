//
// Created by fengxiaotx on 2024/6/4.
//
#include <phecda/sdk/service_init.h>
#include <phecda/sdk/cache.h>
#include <phecda/sdk/provision.h>
#include <phecda/sdk/messaging.h>

namespace phecda::sdk {

    std::shared_ptr<Bootstrap> Bootstrap::newBootstrap(DeviceServiceSDK *sdk) {
        auto bootstrap = std::make_shared<Bootstrap>();
        bootstrap->ds = sdk;
        return bootstrap;
    }

    bool Bootstrap::bootstrapHandler(const bootstrap::BootstrapHandlerArgs &args) {
        auto dic = args.dic;
        ds->_autoEventManager = container::autoEventManagerFrom(dic);

        cache::initCache(ds->_serviceKey, ds->_baseServiceName, dic);

        if (ds->asyncReadingsEnabled()) {

        }

        //region driver initialize
        ds->driver->initialize(ds);
        //endregion
        phecda::sdk::provision::loadProfiles(ds->_config->device.profilesDir, dic);
        phecda::sdk::provision::loadDevices(ds->_config->device.devicesDir, dic);
        ds->_autoEventManager->startAutoEvents();
        return true;
    }

    std::shared_ptr<MessagingBootstrap> MessagingBootstrap::newMessagingBootstrap(const std::string &baseServiceName) {
        auto bootstrap = std::make_shared<MessagingBootstrap>();
        bootstrap->baseServiceName = baseServiceName;
        return bootstrap;
    }

    bool MessagingBootstrap::bootstrapHandler(const bootstrap::BootstrapHandlerArgs &args) {
        if (!messagingBootstrapHandler(args)) {
            return false;
        }
        return true;
    }
}