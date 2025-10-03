#pragma once
#include "../Shader/Shader.h"
#include "../Utils/Utils.h"

class Material : public IDisposable {
protected:
    static constexpr float DEFAULT_SHININESS {0.0f};
    std::string name;
    float shininess;
public:
    explicit Material(std::string name, float shininess = DEFAULT_SHININESS);
    void SetName(const std::string &name);
    NODISCARD std::string GetName() const;
    virtual void Apply(Shader *shader) = 0;
    void Dispose() override = 0;
};
