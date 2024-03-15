#include "Engine/Models/RawModel.hpp"
#include <cstdlib>
#include <iostream>

using namespace MyEngine::Models;

RawModel::RawModel(GLuint id, GLuint vertexCount, const std::array<glm::vec2, 3>& extremes) : m_vaoID(id), m_vertexCount(vertexCount), m_extremes(extremes), m_boundingSizes(CalculateBoundingSizes()) {}

RawModel::RawModel(GLuint id, GLuint vertexCount) : m_vaoID(id), m_vertexCount(vertexCount) {}

glm::vec3 RawModel::CalculateBoundingSizes() {
    float xMax = m_extremes[0][0];
    float xMin = m_extremes[0][1];

    float yMax = m_extremes[1][0];
    float yMin = m_extremes[1][1];

    float zMax = m_extremes[2][0];
    float zMin = m_extremes[2][1];
    
    float sizeX = std::abs(xMax) + std::abs(xMin);
    float sizeY = std::abs(yMax) + std::abs(yMin);
    float sizeZ = std::abs(zMax) + std::abs(zMin);
    return { sizeX, sizeY, sizeZ };
}

void RawModel::SetExtremes(std::array<glm::vec2, 3> newExtremes) {
    m_extremes = newExtremes;
    m_boundingSizes = CalculateBoundingSizes();
}

GLuint RawModel::GetID() const { return m_vaoID; }
GLuint RawModel::GetVertexCount() const { return m_vertexCount; }
const std::array<glm::vec2, 3>& RawModel::GetExtremes() const { return m_extremes; }
glm::vec3& RawModel::GetBoundingSizes() { return m_boundingSizes; }
