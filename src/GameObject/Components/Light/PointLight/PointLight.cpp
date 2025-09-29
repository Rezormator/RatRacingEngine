#include "PointLight.h"

PointLight::PointLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
    const float distance, const float intensity, const glm::vec3 &position, const int index)
    : Light(ambient, diffuse, specular, position, DEFAULT_ROTATION),
      distance(distance), intensity(intensity) {
    PointLight::SetIndex(index);
    CalculateValues();
}

void PointLight::CalculateValues() {
    linear = (CONSTANT / intensity - CONSTANT) * ALPHA / distance;
    quadratic = (CONSTANT - ALPHA) * (CONSTANT / intensity - CONSTANT) / (distance * distance);
}

void PointLight::SetDistance(const float distance) {
    this->distance = distance;
    CalculateValues();
}

void PointLight::SetIntensity(const float intensity) {
    this->intensity = intensity;
    CalculateValues();
}

float PointLight::GetDistance() const {
    return distance;
}

float PointLight::GetIntensity() const {
    return intensity;
}

void PointLight::SetIndex(const int index) {
    lightName = "pointLights[" + std::to_string(index) + ']';
}

void PointLight::Render(Shader *shader) const {
    Light::Render(shader);
    shader->SetVec3(lightName + ".position", position);
    shader->SetFloat(lightName + ".constant", CONSTANT);
    shader->SetFloat(lightName + ".linear", linear);
    shader->SetFloat(lightName + ".quadratic", quadratic);
}
