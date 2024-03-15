#include "Engine/Other/MainFunctions.hpp"
#include "Engine/Globals.hpp"
#include "Engine/Other/Math.hpp"

#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

namespace MyEngine {
    std::random_device rndDevice;
    std::mt19937 rnd(rndDevice());

    // void SpawnRandom(std::vector<Entities::Entity>& entityList, Models::TexturedModel& model, int number, float randRangeFrom, float randRangeTo) {
    //     std::uniform_real_distribution<float> range(randRangeFrom, randRangeTo);

    //     for (int i = 0; i < number; i++) {
    //         float x = range(rnd);
    //         float y = range(rnd);
    //         float z = range(rnd);
    //         fprintf(stdout, "%.2f, %.2f, %.2f\n", x, y, z);

    //         entityList.push_back(Entities::Entity(
    //                     model,
    //                     glm::vec3(x, y, z),
    //                     glm::vec3(range(rnd) * 180, range(rnd) * 180, 0),
    //                     glm::vec3(1)
    //         ));
    //     }
    // }

    void SpawnRandom(std::vector<Entities::Light>* entityList, int number, float randRangeFrom, float randRangeTo) {
        std::uniform_real_distribution<float> range(randRangeFrom, randRangeTo);

        for (int i = 0; i < number; i++)
        {
            float x = range(rnd);
            float y = 0;
            float z = range(rnd);
            // fprintf(stdout, "%.2f, %.2f, %.2f\n", x, y, z);

            entityList->push_back
            (
                Entities::Light(glm::vec3(x, y, z), glm::vec3(0, 1, 0), glm::vec3(1, 0.01, 0.002))
            );
        }
    }

    // Models::TexturedModel GetModel(std::string name) {
        // for (Models::TexturedModel& model : Globals::modelList) {
            // if (model.)
        // }
    // }
}
