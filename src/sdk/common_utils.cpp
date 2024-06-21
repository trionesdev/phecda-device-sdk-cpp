//
// Created by fengxiaotx on 2024/6/20.
//

#include "phecda/sdk/common_utils.h"

namespace phecda::sdk {

    void sendEvent(contracts::Event event, std::string correlationID, std::shared_ptr<bootstrap::DiContainer> dic) {};

    void addEventTags(contracts::Event event) {};

    void addReadingTags(contracts::BaseReading) {};

} // phecda