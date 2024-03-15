#include "Engine/Rendering/OBJLoader.hpp"
#include "Engine/Rendering/Loader.hpp"

#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

namespace MyEngine {
    using namespace Rendering;

    typedef std::array<std::array<int, 3>, 3> ProcessedFace;

    glm::vec3 LoadIntoVec3(std::istringstream& buffer) {
        std::array<std::string, 3> arr;
        buffer.seekg(2);
        buffer >> arr[0] >> arr[1] >> arr[2];

        float floats[3];
        for (unsigned long i = 0; i < arr.size(); i++) { floats[i] = std::stof(arr[i]); }

        return { floats[0], floats[1], floats[2] };
    }

    glm::vec2 LoadIntoVec2(std::istringstream& buffer) {
        std::array<std::string, 2> arr;
        buffer.seekg(2);
        buffer >> arr[0] >> arr[1];

        float floats[2];
        for (unsigned long i = 0; i < arr.size(); i++) { floats[i] = std::stof(arr[i]); }

        return { floats[0], floats[1] };
    }

    ProcessedFace ProcessFace(std::istringstream& buffer) {
        std::array<std::string, 3> face;

        buffer.seekg(2);
        buffer >> face[0] >> face[1] >> face[2];

        // face[i] = "positionNum/textureNum/normalNum"

        std::array<int, 3> i_positions = {0};
        std::array<int, 3> i_textures = {0};
        std::array<int, 3> i_normals = {0};

        int counter = -1;
        for (int i = 0; i < 3; i++) {
            std::string str, final;
            for (unsigned long j = 0; j < face[i].size(); j++) {
                char c = face[i].at(j);

                if (c == '/') {
                    switch (++counter) {
                        case 0:
                            i_positions[i] = std::stoi(str);
                            break;
                        case 1:
                            i_textures[i] = std::stoi(str);
                            break;
                    }

                    str = "";
                    continue;
                }
                str += c;
            }

            i_normals[i] = std::stoi(str);
            counter = -1;
        }

        return { i_positions, i_textures, i_normals };
    }

    Models::RawModel OBJLoader::LoadOBJModel(const std::string& fileName) {
        std::vector<GLfloat> positions;
        std::vector<GLfloat> textures;
        std::vector<GLfloat> normals;
        std::vector<GLuint> indices;

        std::vector<glm::vec3> positionVecIndices;
        std::vector<glm::vec2> textureVecIndices;
        std::vector<glm::vec3> normalVecIndices;

        float xMin = (float)INT_MAX,
            xMax = (float)INT_MIN,
            yMin = (float)INT_MAX,
            yMax = (float)INT_MIN,
            zMin = (float)INT_MAX,
            zMax = (float)INT_MIN;

        if (!Loader::DoesFileExist("res/models/" + fileName)) {
            exit(EXIT_FAILURE);
        }
        std::ifstream file("res/models/" + fileName);
        std::stringstream buffer;
        buffer << file.rdbuf();

        int indexCount = 0;
        std::string line;
        while (std::getline(buffer, line)) {
            std::istringstream stream(line);

            stream.seekg(std::ios_base::beg);

            if (stream.peek() == 'v') {
                stream.seekg(1);

                if (stream.peek() == ' ')      {
                    glm::vec3 vertex = LoadIntoVec3(stream);
                    positionVecIndices.push_back(vertex);

                    // std::cout << "vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";

                    if (vertex.x < xMin) xMin = vertex.x;
                    else if (vertex.x > xMax) xMax = vertex.x;

                    if (vertex.y < yMin) yMin = vertex.y;
                    else if (vertex.y > yMax) yMax = vertex.y;

                    if (vertex.z < zMin) zMin = vertex.z;
                    else if (vertex.z > zMax) zMax = vertex.z;
                }
                else if (stream.peek() == 'n') { normalVecIndices.push_back(LoadIntoVec3(stream)); }
                else if (stream.peek() == 't') { textureVecIndices.push_back(LoadIntoVec2(stream)); }
            }
            else if (stream.peek() == 'f') {
                // [0][?]: position indices, [1][?]: texture indices, [2][?]: normal indices
                ProcessedFace face = ProcessFace(stream);

                for (int i = 0; i < 3; i++) {
                    // - 1 everywhere because obj files start counting from 1

                    positions.push_back(positionVecIndices.at(face[0][i] - 1).x);
                    positions.push_back(positionVecIndices.at(face[0][i] - 1).y);
                    positions.push_back(positionVecIndices.at(face[0][i] - 1).z);

                    // indices.push_back(face[0][i] - 1);
                }

                for (int i = 0; i < 3; i++) {
                    textures.push_back(textureVecIndices.at(face[1][i] - 1).x);
                    textures.push_back(textureVecIndices.at(face[1][i] - 1).y);
                }

                for (int i = 0; i < 3; i++) {
                    normals.push_back(normalVecIndices.at(face[2][i] - 1).x);
                    normals.push_back(normalVecIndices.at(face[2][i] - 1).y);
                    normals.push_back(normalVecIndices.at(face[2][i] - 1).z);
                }

                for (int i = 0; i < 3; i++) {
                    indices.push_back(indexCount);
                    indexCount++;
                }
            }
        }

        // for (glm::vec3 v : positionVecIndices) {
        //     positions.push_back(v.x);
        //     positions.push_back(v.y);
        //     positions.push_back(v.z);
        // }

        // std::cout << "Positions: " << positions.size() / 3 << "\nTriangles: " << positions.size() / 3 / 3 << "\n\n";

        // std::cout << "\nxMax: " << xMax << "  xMin: " << xMin << "\n";
        // std::cout << "yMax: " << yMax << "  yMin: " << yMin << "\n";
        // std::cout << "zMax: " << zMax << "  zMin: " << zMin << "\n\n";

        std::array<glm::vec2, 3> extremes = {
            glm::vec2(xMax, xMin),
            glm::vec2(yMax, yMin),
            glm::vec2(zMax, zMin)
        };

        return Loader::LoadToVAO(positions, indices, textures, normals, extremes);
    }
}
