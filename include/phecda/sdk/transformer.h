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
    const std::string Overflow = "overflow";
    const std::string NaN = "NaN";

    void transformWriteParameter(const CommandValue &cv, const contracts::ResourceProperties &pv);

    void validateWriteMaximum(std::any value, double maximum);

    void transformReadResult(CommandValue cv, contracts::ResourceProperties pv);

    CommandValue mapCommandValue(CommandValue value, std::map<std::string, std::string> mappings);

    std::optional<phecda::contracts::Event> commandValuesToEvent(
            const std::list<CommandValue> &cvs, const std::string &deviceName, const std::string &sourceName,
            bool dataTransform,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    );

    contracts::BaseReading
    commandValueToReading(CommandValue cv, std::string deviceName, std::string profileName, std::string mediaType,
                          long eventOrigin);

}

#endif //PHECDA_DEVICE_SDK_TRANSFORMER_H
