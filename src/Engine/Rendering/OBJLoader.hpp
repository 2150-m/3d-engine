#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Engine/Models/RawModel.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace MyEngine {
    namespace Rendering {
        class OBJLoader {
            public:
                static Models::RawModel LoadOBJModel(const std::string&);

                // template<typename T>
                // static void LoadIntoVector(std::istringstream& stream, std::vector<T>& vec, size_t size);
                // static void LoadIntoStrVector(std::istringstream&, std::vector<std::string>&);
        };
    }
}

#endif
