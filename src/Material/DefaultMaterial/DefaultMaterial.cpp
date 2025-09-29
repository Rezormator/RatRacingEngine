#include "DefaultMaterial.h"
#include "../../Utils/Utils.h"

DefaultMaterial::DefaultMaterial(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular,
                                 float shininess, const glm::vec3 emission)
    : Material(shininess), ambient(ambient), diffuse(diffuse), specular(specular), emission(emission) {
}

DefaultMaterial::DefaultMaterial(const aiDefaultMaterial& material) {
    ambient = Utils::Color3DToVec3(material.ambient);
    diffuse = Utils::Color3DToVec3(material.diffuse);
    specular = Utils::Color3DToVec3(material.specular);
    emission = Utils::Color3DToVec3(material.emission);
    shininess = material.shininess;
}

void DefaultMaterial::Apply(Shader *shader) {
    shader->SetVec3("material.ambient", ambient);
    shader->SetVec3("material.diffuse", diffuse);
    shader->SetVec3("material.specular", specular);
    shader->SetVec3("material.emission", emission);
    shader->SetFloat("material.shininess", shininess);
    shader->SetInt("isLight", false);
    shader->SetInt("isTextureMaterial", false);
}
