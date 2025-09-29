#include "Vertex.h"

Vertex::Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoords)
    : position(position), normal(normal), texCoords(texCoords) {
}

GLvoid Vertex::setPosition(const aiVector3D &position) {
    this->position = {position.x, position.y, position.z};
}

GLvoid Vertex::setNormal(const aiVector3D &normal) {
    this->normal = {normal.x, normal.y, normal.z};
}

GLvoid Vertex::setTexCoords(const aiVector3D &texCoords) {
    this->texCoords = {texCoords.x, texCoords.y};
}
