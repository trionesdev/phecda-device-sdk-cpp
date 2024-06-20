//
// Created by fengxiaotx on 2024/6/4.
//

#ifndef PHECDA_DEVICE_SDK_PROVISION_H
#define PHECDA_DEVICE_SDK_PROVISION_H

#include <string>
#include <memory>
#include <phecda/bootstrap/di-container.h>

namespace phecda::sdk::provision {

    enum class FileType {
        YAML,
        JSON,
        OTHER
    };

    void loadProfiles(const std::string& path, const std::shared_ptr<bootstrap::DiContainer>& dic);

    void loadDevices(const std::string& path, std::shared_ptr<bootstrap::DiContainer> dic);
}
#endif //PHECDA_DEVICE_SDK_PROVISION_H
