#ifndef MODULE_MANAGER_HPP
#define MODULE_MANAGER_HPP

#include <vector>
#include <memory>
#include "module_interface.hpp"

namespace cxc {

    class ModuleManager {
        private:
            std::vector<std::unique_ptr<ModuleInterface>> modules;

        public:
            //Register a new module
            void register_module(std::unique_ptr<ModuleInterface> module);

            //Initialize all registered modules
            void init_modules();

            //Shutdown all registered modules
            void shutdown_modules();

            //Pass a request to all the modules and collect responses 
            std::string handle_request(const std::string& request);

    };
}

#endif  //MODULE_MANAGER_HPP