//
// Created by fengxiaotx on 2024/6/4.
//
#include <phecda/sdk/service.h>
#include <phecda/sdk/cache.h>
#include <phecda/sdk/ProtocolDriver.h>
#include <phecda/sdk/provision.h>

namespace phecda::sdk {

    std::shared_ptr<Bootstrap> Bootstrap::newBootstrap(DeviceServiceSDK *sdk) {
        auto bootstrap = std::make_shared<Bootstrap>();
        bootstrap->ds = sdk;
        return bootstrap;
    }

    bool Bootstrap::bootstrapHandler(bootstrap::BootstrapHandlerArgs args) {
        auto dic = args.dic;
        ds->autoEventManager_ = container::autoEventManagerFrom(dic);

        cache::initCache(ds->serviceKey_, ds->baseServiceName_, dic);

        if (ds->asyncReadingsEnabled()) {

        }

        //region driver initialize
        ds->driver->initialize(ds);
        //endregion

        phecda::sdk::provision::loadProfiles(ds->config->device.profilesDir, dic);
        phecda::sdk::provision::loadDevices(ds->config->device.devicesDir, dic);

        ds->autoEventManager_->startAutoEvents();
        return true;
    }

    std::shared_ptr<MessagingBootstrap> MessagingBootstrap::newMessagingBootstrap(const std::string& baseServiceName) {
        auto bootstrap = std::make_shared<MessagingBootstrap>();
        bootstrap->baseServiceName = baseServiceName;
        return bootstrap;
    }

    bool MessagingBootstrap::bootstrapHandler(bootstrap::BootstrapHandlerArgs args) {
        return true;
    }
}