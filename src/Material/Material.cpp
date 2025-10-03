#include "Material.h"
#include <utility>

Material::Material(std::string name, const float shininess) : name(std::move(name)), shininess(shininess) {
}

void Material::SetName(const std::string &name) {
    this->name = name;
}

std::string Material::GetName() const {
    return name;
}
