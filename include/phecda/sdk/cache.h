//
// Created by fengxiaotx on 2024/5/22.
//
#include <string>
#include <phecda/bootstrap/di-container.h>

namespace phecda::sdk {


    class DeviceCache {
    };

    class ProfileCache {
    };

    static DeviceCache dc;
    static ProfileCache pc;

    static void initCache(std::string instanceName, std::string baseServiceName, bootstrap::DiContainer *dic);

}