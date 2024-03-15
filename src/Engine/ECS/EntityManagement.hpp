#ifndef ENTITYMNG
#define ENTITYMNG

#include "Engine/Globals.hpp"

namespace MyEngine {
    namespace Entities {
        unsigned GenerateID();
        unsigned CreateEntity(std::string name, Models::TexturedModel model, glm::vec3 position);
    }
}

#endif
