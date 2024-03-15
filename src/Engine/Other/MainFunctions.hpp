#ifndef MAINFUNS_H
#define MAINFUNS_H

#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/ECS/Entities/Light.hpp"
#include "Engine/Models/TexturedModel.hpp"
#include "Engine/Rendering/Loader.hpp"

#include <GL/gl.h>
#include <sstream>
#include <vector>

namespace MyEngine {
    // void SpawnRandom(std::vector<Entities::Entity>& entityList, Models::TexturedModel& model, int number, float, float);
    void SpawnRandom(std::vector<Entities::Light>* entityList, int number, float, float);

    Models::TexturedModel GetModel(std::string name);
}

#endif
