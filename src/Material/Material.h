#pragma once
#include "../Shader/Shader.h"

class Material {
protected:
    static constexpr float DEFAULT_SHININESS {0.0f};
    float shininess;
public:
    explicit Material(float shininess = DEFAULT_SHININESS);
    virtual ~Material() = default;
    virtual void Apply(Shader *shader) = 0;
};
