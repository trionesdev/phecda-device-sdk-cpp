//
// Created by fengxiaotx on 2024/6/3.
//

#include "phecda/bootstrap/Processor.h"


namespace phecda::bootstrap {
    Processor *Processor::newProcessor(CommonArgs *args, Variables *variables, Timer *startupTimer, Container *dic) {
        auto *processor = new Processor();
        processor->args = args;
        processor->variables = variables;
        processor->startupTimer = startupTimer;
        processor->dic = dic;
        return processor;
    }

    std::string getConfigFileLocation(CommonArgs *args_) {
        std::string configFileName = Variables::getConfigFileName(args_->configFileName());
        std::string configDir = Variables::getConfigDir(args_->configDirectory());
        std::string profileDir = Variables::getProfileDir(args_->profile());
        return "";
    }

    void Processor::process(std::string serviceKey, Configuration *serviceConfig) {
        std::string filePath = getConfigFileLocation(args);
    }
} // bootstrap
// phecda