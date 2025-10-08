#pragma once
#include "glm/glm.hpp"
#include <string>

struct cameraJson {
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float fov;
    float nearPlane;
    float farPlane;
};

struct gameObjectJson {
    std::string model;
    glm::mat4 transform;
};