#pragma once
#include <string>
#include "../GameObject/Components/Model/Model.h"
#include "../Material/Material.h"

namespace Resources {
    void LoadModel(const std::string &modelDirectory);
    Material *GetMaterialByIndex(uint index);
    uint GetMaterialIndexByName(const std::string &name);
    Model *GetModelByIndex(uint index);
    uint GetModelIndexByName(const std::string &name);
    Mesh *GetMeshByIndex(uint index);
    void Dispose();
}
