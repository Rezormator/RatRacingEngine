#pragma once
#include <vector>
#include "Mesh/Mesh.h"

class Model {
private:
    std::string name;
    std::vector<uint> meshes;
public:
    explicit Model(const std::string &name, const std::vector<uint> &meshes);
    void SetName(const std::string &name);
    void SetMeshes(const std::vector<uint> &meshes);
    NODISCARD std::string GetName() const;
    NODISCARD std::vector<uint> GetMeshes() const;
};
