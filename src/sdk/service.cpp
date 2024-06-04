//
// Created by fengxiaotx on 2024/6/4.
//
#include <phecda/sdk/service.h>
#include <phecda/sdk/cache.h>
#include <utility>
#include <phecda/sdk/ProtocolDriver.h>
#include <phecda/sdk/provision.h>

namespace phecda::sdk {

    Bootstrap *Bootstrap::newBootstrap(DeviceServiceSDK *sdk) {
        auto *bootstrap = new Bootstrap();
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

        ds->autoEventManager_->startAutoEvents();
        return true;
    }

    MessagingBootstrap *MessagingBootstrap::newMessagingBootstrap(std::string baseServiceName) {
        auto *bootstrap = new MessagingBootstrap();
        bootstrap->baseServiceName = std::move(baseServiceName);
        return bootstrap;
    }

    bool MessagingBootstrap::bootstrapHandler(bootstrap::BootstrapHandlerArgs args) {
        return true;
    }
}