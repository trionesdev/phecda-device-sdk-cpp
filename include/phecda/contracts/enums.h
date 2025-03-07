//
// Created by fengxiaotx on 2024/5/22.
//

#ifndef PHECDA_DEVICE_ENUMS_H
#define PHECDA_DEVICE_ENUMS_H
namespace phecda::contracts {
    enum AdminState {
        LOCKED,
        UNLOCKED
    };

    enum OperatingState {
        UP,
        DOWN,
        UNKNOWN
    };

}
#endif //PHECDA_DEVICE_ENUMS_H
