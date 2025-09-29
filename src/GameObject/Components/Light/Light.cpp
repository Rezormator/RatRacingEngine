#include "Light.h"

#include <utility>

Light::Light(const glm::vec3 &ambient, const glm::vec3 &diffuse,
             const glm::vec3 &specular, const glm::vec3 &position, const glm::vec3 &rotation)
    : GameObject(position, rotation), ambient(ambient), diffuse(diffuse), specular(specular) {
}

void Light::SetAmbient(const glm::vec3 &ambient) {
    this->ambient = ambient;
}

void Light::SetDiffuse(const glm::vec3 &diffuse) {
    this->diffuse = diffuse;
}

void Light::SetSpecular(const glm::vec3 &specular) {
    this->specular = specular;
}

glm::vec3 Light::GetAmbient() const {
    return this->ambient;
}

glm::vec3 Light::GetDiffuse() const {
    return this->diffuse;
}

glm::vec3 Light::GetSpecular() const {
    return this->specular;
}

void Light::Render(Shader *shader) const {
    shader->SetVec3(lightName + ".ambient", ambient);
    shader->SetVec3(lightName + ".diffuse", diffuse);
    shader->SetVec3(lightName + ".specular", specular);
}
