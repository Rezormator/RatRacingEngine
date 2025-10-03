#pragma once
#include "../Material.h"
#include "../../Dispose/IDisposable.h"
#include "Texture/Texture.h"

struct aiTextureMaterial {
    std::string name;
    Texture *diffuse;
    Texture *specular;
    Texture *emission;
    float shininess;
};

class TextureMaterial final : public Material {
private:
    Texture *diffuse;
    Texture *specular;
    Texture *emission;
public:
    explicit TextureMaterial(const std::string &name, Texture *diffuse = nullptr, Texture *specular = nullptr,
                             Texture *emission = nullptr, float shininess = DEFAULT_SHININESS);
    explicit TextureMaterial(const aiTextureMaterial &material);
    void Apply(Shader *shader) override;
    void Dispose() override;
};
