#include "SpotLight.h"

SpotLight::SpotLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
    const float distance, const float intensity, const float innerCutOff, const float outerCutOff,
    const glm::vec3 &position, const glm::vec3 &rotation, const int index)
    : PointLight(ambient, diffuse, specular, distance, intensity, position, index), innerCutOff(innerCutOff),
      outerCutOff(outerCutOff) {
    SpotLight::SetIndex(index);
    SetRotation(rotation);
}

void SpotLight::SetInnerCutOff(const float innerCutOff) {
    this->innerCutOff = innerCutOff;
}

void SpotLight::SetOuterCutOff(const float outerCutOff) {
    this->outerCutOff = outerCutOff;
}

float SpotLight::GetInnerCutOff() const {
    return innerCutOff;
}

float SpotLight::GetOuterCutOff() const {
    return outerCutOff;
}

void SpotLight::SetIndex(const int index) {
    lightName = "spotLights[" + std::to_string(index) + ']';
}

void SpotLight::Render(Shader *shader) const {
    PointLight::Render(shader);
    shader->SetVec3(lightName + ".direction", rotation);
    shader->SetFloat(lightName + ".innerCutOff", glm::cos(glm::radians(innerCutOff)));
    shader->SetFloat(lightName + ".outerCutOff", glm::cos(glm::radians(outerCutOff)));
}
