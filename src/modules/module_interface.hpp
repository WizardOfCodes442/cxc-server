#ifndef MODULE_INTERFACE_HPP
#define MODULE_INTERFACE_HPP

#include <string>

namespace cxc {
    class ModuleInterface {
        public:
            virtual ~ModuleInterface() = default;

            //Initialize the module 
            virtual void init() = 0;

            //Shutdown/cleanup the module
            virtual void shutdown() = 0;

            //Handle HTTP requests (Optional)
            virtual std::string handle(const std::string& request) = 0;
    };
}

#endif  //MODULE_INTERFACE_HPP
