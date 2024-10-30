#ifndef LOGGER_MODULE_HPP
#define LOGGER_MODULE_HPP

#include "module_interface.hpp"
#include <iostream>

namespace cxc {
    class LoggerModule : public ModuleInterface {
        public:
            void init() override;
            void shutdown() override;
            std::string handle(const std::string& request) override;
    };
}

#endif  //LOGGER_MODULE_HPP
