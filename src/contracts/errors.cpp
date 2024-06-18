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
        return PhecdaException::error();
    }

    std::string CommonPhecdaException::debugMessages() {
        return PhecdaException::debugMessages();
    }

    std::string CommonPhecdaException::message() {
        return PhecdaException::message();
    }

    int CommonPhecdaException::code() {
        return PhecdaException::code();
    }
}