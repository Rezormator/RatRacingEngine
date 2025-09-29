#pragma once
#include "../Light.h"

class PointLight : public Light {
private:
    float distance;
    float intensity;
    float linear;
    float quadratic;
    void CalculateValues();
protected:
    static constexpr float CONSTANT = 1.0f;
    static constexpr float ALPHA = 0.5f;
public:
    PointLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float distance,
        float intensity, const glm::vec3 &position = DEFAULT_POSITION, int index = DEFAULT_INDEX);
    void SetDistance(float distance);
    void SetIntensity(float intensity);
    NODISCARD float GetDistance() const;
    NODISCARD float GetIntensity() const;
    void SetIndex(int index) override;
    void Render(Shader *shader) const override;
};
