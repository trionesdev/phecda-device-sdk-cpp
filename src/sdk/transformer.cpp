//
// Created by fengxiaotx on 2024/6/18.
//
#include "phecda/sdk/transformer.h"
#include <iostream>

namespace phecda::sdk::transformer {
    void transformWriteParameter(const CommandValue &cv, const contracts::ResourceProperties &pv) {
        std::cout << "sss" << std::endl;
    }

    void validateWriteMaximum(std::any value, double maximum) {
        std::cout << "sss" << std::endl;
    };

    std::optional<phecda::contracts::Event> commandValuesToEvent(
            const std::list<CommandValue> &cvs, const std::string &deviceName, const std::string &sourceName,
            bool dataTransform,
            const std::shared_ptr<bootstrap::DiContainer> &dic
    ) {
        return std::nullopt;
    }

}