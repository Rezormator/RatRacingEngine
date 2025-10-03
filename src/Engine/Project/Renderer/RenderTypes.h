#pragma once
#include <glm/glm.hpp>

struct renderCamera {
    glm::vec3 position;
    glm::mat4 projectionMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
};

struct render {

};