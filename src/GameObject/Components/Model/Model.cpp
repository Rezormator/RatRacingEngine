#include "Model.h"
#include <iostream>
#include "../../../Error/Error.h"
#include "../../../Material/TextureMaterial/TextureMaterial.h"

Model::Model(const std::string &name, const std::vector<uint> &meshes)
    : name(name), meshes(meshes) {
}

void Model::SetName(const std::string &name) {
    this->name = name;
}

void Model::SetMeshes(const std::vector<uint> &meshes) {
    this->meshes = meshes;
}

std::string Model::GetName() const {
    return name;
}

std::vector<uint> Model::GetMeshes() const {
    return meshes;
}
