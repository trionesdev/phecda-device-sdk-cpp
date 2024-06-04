//
// Created by fengxiaotx on 2024/6/4.
//

#ifndef PHECDA_DEVICE_SDK_PROVISION_H
#define PHECDA_DEVICE_SDK_PROVISION_H

#include <string>
#include <phecda/bootstrap/di-container.h>

namespace phecda::sdk::provision {

    enum class FileType {
        YAML,
        JSON,
        OTHER
    };

    void loadProfiles(std::string path, phecda::bootstrap::DiContainer *container);

    void loadDevices(std::string path, phecda::bootstrap::DiContainer *container);
}
#endif //PHECDA_DEVICE_SDK_PROVISION_H
