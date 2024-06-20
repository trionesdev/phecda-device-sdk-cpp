//
// Created by fengxiaotx on 2024/6/18.
//

#ifndef PHECDA_DEVICE_SDK_CONTRACTS_CONSTANTS_H
#define PHECDA_DEVICE_SDK_CONTRACTS_CONSTANTS_H

#include <string>

namespace phecda::contracts::constants {
    static std::string NAME = "name";
    static std::string COMMAND = "command";

    static std::string READ_WRITE_R = "R";
    static std::string READ_WRITE_W = "W";
    static std::string READ_WRITE_RW = "RW";
    static std::string READ_WRITE_WR = "WR";

    //region Constants related to Reading ValueTypes
    static std::string VALUE_TYPE_BOOL = "Bool";
    static std::string VALUE_TYPE_STRING = "String";
    static std::string VALUE_TYPE_INT = "Int";
    static std::string VALUE_TYPE_LONG = "Long";
    static std::string VALUE_TYPE_FLOAT = "Float";
    static std::string VALUE_TYPE_DOUBLE = "Double";
    static std::string VALUE_TYPE_OBJECT = "Object";
    static std::string VALUE_TYPE_BOOL_ARRAY = "BoolArray";
    static std::string VALUE_TYPE_STRING_ARRAY = "StringArray";
    static std::string VALUE_TYPE_INT_ARRAY = "IntArray";
    static std::string VALUE_TYPE_LONG_ARRAY = "LongArray";
    static std::string VALUE_TYPE_FLOAT_ARRAY = "FloatArray";
    static std::string VALUE_TYPE_DOUBLE_ARRAY = "DoubleArray";
    static std::string VALUE_TYPE_OBJECT_ARRAY = "ObjectArray";
    //endregion

}

#endif //PHECDA_DEVICE_SDK_CONTRACTS_CONSTANTS_H
