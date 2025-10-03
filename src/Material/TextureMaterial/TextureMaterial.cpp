#include "TextureMaterial.h"

TextureMaterial::TextureMaterial(const std::string &name, Texture *diffuse, Texture *specular, Texture *emission, const float shininess)
    : Material(name, shininess), diffuse(diffuse), specular(specular), emission(emission) {
}

TextureMaterial::TextureMaterial(const aiTextureMaterial &material) : Material(material.name, material.shininess) {
    diffuse = material.diffuse;
    specular = material.specular;
    emission = material.emission;
}

void TextureMaterial::Apply(Shader *shader) {
    shader->SetInt("textureMaterial.diffuse", 0);
    shader->SetInt("textureMaterial.specular", 1);
    shader->SetInt("textureMaterial.emission", 2);
    shader->SetFloat("textureMaterial.shininess", shininess);
    glActiveTexture(GL_TEXTURE0);
    diffuse->Bind();
    glActiveTexture(GL_TEXTURE1);
    specular->Bind();
    glActiveTexture(GL_TEXTURE2);
    emission->Bind();
    shader->SetInt("isLight", false);
    shader->SetInt("isTextureMaterial", true);
}

void TextureMaterial::Dispose() {
    delete diffuse;
    delete specular;
    delete emission;
}
