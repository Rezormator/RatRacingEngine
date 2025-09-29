#pragma once
#include "../Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
        const glm::vec3 &rotation = DEFAULT_ROTATION, int index = DEFAULT_INDEX);
    void SetIndex(int index) override;
    void Render(Shader *shader) const override;
};
