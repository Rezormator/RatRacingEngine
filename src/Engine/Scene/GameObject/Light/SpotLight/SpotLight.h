#pragma once
#include "../PointLight/PointLight.h"

class SpotLight : public PointLight {
private:
    float innerCutOff;
    float outerCutOff;
public:
    SpotLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float distance,
        float intensity, float innerCutOff, float outerCutOff, const glm::vec3 &position = DEFAULT_POSITION,
        const glm::vec3 &rotation = DEFAULT_ROTATION, int index = DEFAULT_INDEX);
    void SetInnerCutOff(float innerCutOff);
    void SetOuterCutOff(float outerCutOff);
    NODISCARD float GetInnerCutOff() const;
    NODISCARD float GetOuterCutOff() const;
    void SetIndex(int index) override;
    void Render(Shader *shader) const override;
};
