//
// Created by fengxiaotx on 2024/6/18.
//

#ifndef PHECDA_DEVICE_SDK_ERRORS_H
#define PHECDA_DEVICE_SDK_ERRORS_H

#include <string>
#include <utility>

namespace phecda::contracts {
    class PhecdaException {
    public:
        virtual std::string error() = 0;

        virtual std::string debugMessages() = 0;

        virtual std::string message() = 0;

        virtual int code() = 0;
    };

    class CommonPhecdaException : public PhecdaException, public std::exception {
    private:
        std::string _callerInfo;
        std::string _kind;
        std::string _message;
        int _code{};
        std::exception _err;

    public:
        static CommonPhecdaException newCommandPhecdaException(const std::string &kind, const std::string &message,
                                                               const std::exception &wrappedErr);

        CommonPhecdaException(std::string kind, std::string message) : _kind(std::move(kind)), _message(std::move(message)) {};

        CommonPhecdaException(std::string message) : _message(std::move(message)) {};

        CommonPhecdaException() = default;

        char const* what() const override;

        std::string error() override;

        std::string debugMessages() override;

        std::string message() override;

        int code() override;

        std::string kind();

    };
    namespace error_kind{
        const std::string KIND_UN_KNOW = "Unknown";
        const std::string KIND_DATABASE_ERROR = "Database";
        const std::string KIND_COMMUNICATION_ERROR = "Communication";
        const std::string KIND_ENTITY_DOSE_NOT_EXIST = "NotFound";
        const std::string KIND_CONTRACT_INVALID = "ContractInvalid";
        const std::string KIND_SERVER_ERROR = "UnexpectedServerError";
        const std::string KIND_DUPLICATE_NAME = "DuplicateName";
        const std::string KIND_INVALID_ID = "InvalidId";
        const std::string KIND_NOT_ALLOWED = "NotAllowed";
        const std::string KIND_SERVICE_LOCKED = "ServiceLocked";
        const std::string KIND_OVERFLOW_ERROR = "OverflowError";
        const std::string KIND_NAN_ERROR = "NaNError";
    }
}
#endif //PHECDA_DEVICE_SDK_ERRORS_H
