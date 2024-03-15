#include "Engine/ECS/Components/RayComponent.hpp"
#include "RayComponent.hpp"

namespace MyEngine {
    namespace Components {
        RayComponent::RayComponent(unsigned entityID, float length, bool debug)
            : m_entityID(entityID), m_length(length), m_visualDebugging(debug)
        {}
    }
}

