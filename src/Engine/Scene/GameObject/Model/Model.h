#pragma once

#include <map>
#include <vector>
#include "../GameObject.h"
#include "Material/Material.h"
#include "Mesh/Mesh.h"
#include <assimp/scene.h>

class Model final : public GameObject {
private:
    std::string directory;
    std::vector<Mesh *> meshes;
    std::map<GLuint, Material *> materials;
    void LoadModel(const std::string &path);
    void LoadMaterials(const aiScene *scene);
    void ProcessNode(const aiNode *node, const aiScene *scene);
    void UpdateTransform() override;
public:
    explicit Model(const char *path);
    ~Model() override;
    void SetModel(const glm::mat4 &model) override;
    std::string GetDirectory() const;
    void Render(Shader *shader) const override;
};
