//
// Created by fengxiaotx on 2024/6/28.
//

#ifndef PHECDA_DEVICE_SDK_LOG_H
#define PHECDA_DEVICE_SDK_LOG_H

#include <log4cxx/logger.h>

#define LOG_INFO(logger, message) LOG4CXX_INFO(logger,  __LINE__ << " " << message)
#define LOG_DEBUG(logger, message) LOG4CXX_DEBUG(logger,  __LINE__ << " " << message)
#define LOG_WARN(logger, message) LOG4CXX_WARN(logger,  __LINE__ << " " << message)
#define LOG_ERROR(logger, message) LOG4CXX_ERROR(logger,  __LINE__ << " " << message)
#define LOG_FATAL(logger, message) LOG4CXX_FATAL(logger, __LINE__ << " " << message)
#define LOG_TRACE(logger, message) LOG4CXX_TRACE(logger,  __LINE__ << " " << message)


#endif //PHECDA_DEVICE_SDK_LOG_H
