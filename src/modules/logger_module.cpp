#include "logger_module.hpp"

namespace cxc {
    void LoggerModule::init() {
        std::cout <<"LoggerModule initialized. \n";
    }

    void LoggerModule::shutdown() {
        std::cout <<"LoggerModule shutdown\n";
    }

    std::string LoggerModule::handle(const std::string& request) {
        std::cout <<"Logging request: " << request << std::endl;
        return "LoggerModule: Request logged.";
    }
}