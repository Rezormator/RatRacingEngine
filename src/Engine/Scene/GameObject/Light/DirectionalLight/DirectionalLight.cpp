#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
    const glm::vec3 &rotation, const int index)
    : Light(ambient, diffuse, specular, DEFAULT_POSITION, rotation) {
    DirectionalLight::SetIndex(index);
}

void DirectionalLight::SetIndex(const int index) {
    lightName = "directionalLights[" + std::to_string(index) + ']';
}

void DirectionalLight::Render(Shader *shader) const {
    Light::Render(shader);
    shader->SetVec3(lightName + ".direction", rotation);
}
