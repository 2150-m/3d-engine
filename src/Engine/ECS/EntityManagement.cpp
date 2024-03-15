#include "Engine/ECS/EntityManagement.hpp"
#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/Other/Printer.hpp"
#include <iostream>
#include <tuple>
#include <utility>

namespace MyEngine {
    unsigned Entities::GenerateID()
    {
        int num = 0;
        while (Globals::entityMap.count(num) > 0) { num++; }
        return num;
    }

    unsigned Entities::CreateEntity(std::string name, Models::TexturedModel model, glm::vec3 position)
    {
        unsigned id = GenerateID();
        Globals::entityMap.try_emplace(id, id, name, model, position); // doing this so it calls the constructor just once
        return id;
    }
}
