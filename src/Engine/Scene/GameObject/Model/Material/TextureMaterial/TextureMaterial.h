#pragma once
#include "../Material.h"
#include "Texture/Texture.h"

struct aiTextureMaterial {
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
    explicit TextureMaterial(Texture *diffuse = nullptr, Texture *specular = nullptr, Texture *emission = nullptr,
                    float shininess = DEFAULT_SHININESS);
    explicit TextureMaterial(const aiTextureMaterial &material);
    ~TextureMaterial() override;
    void Apply(Shader *shader) override;
};
