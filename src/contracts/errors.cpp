//
// Created by fengxiaotx on 2024/6/18.
//
#include "phecda/contracts/errors.h"

namespace phecda::contracts {

    CommonPhecdaException
    CommonPhecdaException::newCommandPhecdaException(const std::string &kind, const std::string &message,
                                                                const std::exception &wrappedErr) {
        CommonPhecdaException ex(message);
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

    const char* CommonPhecdaException::what() const noexcept
    {
        return _message.c_str();
    };

    std::string CommonPhecdaException::kind() {
        return _kind;
    }


}