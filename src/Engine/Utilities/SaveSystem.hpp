#ifndef SAVESYSTEM_HPP
#define SAVESYSTEM_HPP

#include <string>
namespace MyEngine {
    namespace Utilities {
        class SaveSystem {
        public:
            static void Save(const std::string& fileName);
            static void Load();

        private:

        };
    }
}

#endif
