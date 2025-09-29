#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>

struct Vertex {
    static constexpr glm::vec3 DEFAULT_VERTEX_DATA {0.0f};
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    explicit Vertex(const glm::vec3 &position = DEFAULT_VERTEX_DATA,
        const glm::vec3 &normal = DEFAULT_VERTEX_DATA,
        const glm::vec2 &texCoords = DEFAULT_VERTEX_DATA);
    GLvoid setPosition(const aiVector3D &position);
    GLvoid setNormal(const aiVector3D &normal);
    GLvoid setTexCoords(const aiVector3D &texCoords);
};
