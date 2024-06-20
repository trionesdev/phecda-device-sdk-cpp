//
// Created by fengxiaotx on 2024/6/20.
//

#ifndef PHECDA_DEVICE_SDK_TRANSFORMER_H
#define PHECDA_DEVICE_SDK_TRANSFORMER_H

#include <optional>
#include <phecda/sdk/model.h>
#include <phecda/contracts/model.h>
#include <phecda/bootstrap/di-container.h>

namespace phecda::sdk::transformer {
    void transformWriteParameter(const CommandValue &cv, const contracts::ResourceProperties &pv);

    void validateWriteMaximum(std::any value, double maximum);

    std::optional<phecda::contracts::Event> commandValuesToEvent(
            const std::list<CommandValue> &cvs, const std::string &deviceName,const std::string& sourceName, bool dataTransform,
            const std::shared_ptr<bootstrap::DiContainer>& dic
    );

}

#endif //PHECDA_DEVICE_SDK_TRANSFORMER_H
