#pragma once
#include <assimp/types.h>
#include "DefaultMaterial.h"
#include "../Material.h"

struct aiDefaultMaterial {
    aiColor3D ambient;
    aiColor3D diffuse;
    aiColor3D specular;
    aiColor3D emission;
    float shininess;
};

class DefaultMaterial final : public Material {
private:
    static constexpr glm::vec3 DEFAULT_LIGHTING_COMPONENT{0.0f};
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;
public:
    explicit DefaultMaterial(glm::vec3 ambient = DEFAULT_LIGHTING_COMPONENT,
                             glm::vec3 diffuse = DEFAULT_LIGHTING_COMPONENT,
                             glm::vec3 specular = DEFAULT_LIGHTING_COMPONENT,
                             float shininess = DEFAULT_SHININESS,
                             glm::vec3 emission = DEFAULT_LIGHTING_COMPONENT);
    explicit DefaultMaterial(const aiDefaultMaterial& material);
    void Apply(Shader *shader) override;
};
