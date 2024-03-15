#include "SaveSystem.hpp"
#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/Globals.hpp"
#include "Engine/Other/Printer.hpp"

#include <fstream>
#include <sstream>

using namespace MyEngine::Utilities;

void SaveSystem::Save(const std::string& fileName) {
    std::ofstream file{fileName};
    if (!file) {
        Printer::PrintError("Saving failed. Exiting...");
        exit(1);
    }

    file << "{\n";

    for (int i = 0; i < Globals::entityMap.size(); i++) {
        Entities::Entity& e = Globals::entityMap.at(i);

        file << "\t\""              << e.GetID()               << "\": {\n\t\t";
        file << "\"name\": \""      << e.GetName()             << "\",\n\t\t";
        file << "\"parentID\": "    << (int)e.GetParentID()    << ",\n\t\t";

        file << "\"childrenIDs\": [ ";
        for (unsigned id : e.GetChildrenIDs()) {
            file << id << ",";
        }
        file << " ],\n\t\t";

        file << "\"tModel\": { "
            << "\"modelID\": "     << e.GetModel().GetRawModel().GetID()
            << ", \"textureID\": " << e.GetModel().GetTexture().GetID() << " },\n\t\t";

        file << "\"position\": [ " << e.GetPosition().x << ", " << e.GetPosition().y << ", " << e.GetPosition().z << " ],\n\t\t";
        file << "\"rotation\": [ " << e.GetRotation().x << ", " << e.GetRotation().y << ", " << e.GetRotation().z << " ],\n\t\t";
        file << "\"scale\": [ "    << e.GetScale().x    << ", " << e.GetScale().y    << ", " << e.GetScale().z    << " ],\n\t\t";

        file << "\"movable\": "        << e.GetIsMovable()              << ",\n\t\t";
        file << "\"rotatable\": "      << e.GetIsRotatable()            << ",\n\t\t";
        file << "\"scalable\": "       << e.GetIsScalable()             << ",\n\t\t";
        file << "\"followPosition\": " << e.GetIsFollowingPosition()    << ",\n\t\t";
        file << "\"followRotation\": " << e.GetIsFollowingRotation()    << ",\n\t\t";
        file << "\"followScale\": "    << e.GetIsFollowingScale()       << ",\n\t\t";

        file << "\"playerCompPos\": " << (int)e.GetCameraCompPos()      << ",\n\t\t";
        file << "\"aabbCompPos\": "   << (int)e.GetAABBCompPos()        << ",\n\t\t";
        file << "\"obbCompPos\": "    << (int)e.GetOBBCompPos()         << ",\n\t\t";
        file << "\"rbCompPos\": "     << (int)e.GetRigidBodyCompPos()   << ",\n\t\t";
        file << "\"cameraCompPos\": " << (int)e.GetCameraCompPos()      << ",\n\t";

        file << "},\n";
    }

    file << "}\n";
}
