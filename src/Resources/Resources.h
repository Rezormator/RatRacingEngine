#pragma once
#include <string>
#include "../Material/Material.h"

namespace Resources {
    void LoadModel(const std::string &modelDirectory);
    Material *GetMaterialByIndex(uint index);
    uint GetMaterialIndexByName(const std::string &name);
    void Dispose();
}
