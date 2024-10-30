#include "module_manager.hpp"

namespace cxc {
    void ModuleManager::register_module(std::unique_ptr<ModuleInterface> module) {
        modules.push_back(std::move(module));
    }

    void ModuleManager::init_modules() {
        for (auto& module : modules) {
            module->init();
        }
    }

    void ModuleManager::shutdown_modules() {
        for (auto& module: modules) {
            module->shutdown();
        }
    }

    std::string ModuleManager::handle_request(const std::string& request) {
        std::string response;
        for (auto& module : modules) {
            response += module->handle(request) + "\n";
        }
        return response;
    }
}