//
// Created by fengxiaotx on 2024/6/27.
//

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "phecda/util/StringUtils.h"

namespace phecda::util {

    std::string StringUtils::uuid() {
        return boost::uuids::to_string(boost::uuids::random_generator()());
    }
} // phecda