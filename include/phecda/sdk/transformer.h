//
// Created by fengxiaotx on 2024/6/20.
//

#ifndef PHECDA_DEVICE_SDK_TRANSFORMER_H
#define PHECDA_DEVICE_SDK_TRANSFORMER_H

#include <optional>
#include <phecda/sdk/model.h>
#include <phecda/contracts/model.h>
#include <phecda/bootstrap/di_container.h>

namespace phecda::sdk::transformer {
    const double defaultBase = 0.0;
    const double defaultScale = 0.0;
    const double defaultOffset = 0.0;
    const long defaultMask = 0.0l;
    const long defaultShift = 0.0l;
    const std::string Overflow = "overflow";
    const std::string NaN = "NaN";

    void transformWriteParameter( CommandValue cv, const contracts::ResourceProperties &pv);

    void validateWriteMaximum(const std::any &value, double maximum);

    void transformReadResult(CommandValue cv, const contracts::ResourceProperties &pv);

    CommandValue mapCommandValue(CommandValue value, const std::map<std::string, std::string> &mappings);

    std::optional<phecda::contracts::Event> commandValuesToEvent(
            const std::list<CommandValue> &cvs, const std::string &deviceName, const std::string &sourceName,
            bool dataTransform,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    );

    contracts::BaseReading
    commandValueToReading(CommandValue cv, const std::string &deviceName, const std::string &profileName,
                          const std::string &mediaType,
                          long eventOrigin);

}

#endif //PHECDA_DEVICE_SDK_TRANSFORMER_H
