//
// Created by fengxiaotx on 2024/6/18.
//
#include "phecda/contracts/errors.h"

namespace phecda::contracts {

    CommonPhecdaException
    contracts::CommonPhecdaException::newCommandPhecdaException(const std::string &kind, const std::string &message,
                                                                const std::exception &wrappedErr) {
        CommonPhecdaException ex;
        ex._kind = kind;
        ex._message = message;
        ex._err = wrappedErr;
        return ex;
    }

    std::string CommonPhecdaException::error() {
        return "";
    }

    std::string CommonPhecdaException::debugMessages() {
        return "";
    }

    std::string CommonPhecdaException::message() {
        return "";
    }

    int CommonPhecdaException::code() {
        return 0;
    }
}