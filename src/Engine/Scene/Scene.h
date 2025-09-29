#pragma once
#include <string>
#include "GameObject/Camera/Camera.h"
#include "GameObject/Model/Model.h"

class Scene {
private:
    Camera *camera;
    std::map<GLuint, Model *> models;
    std::vector<std::pair<GLuint, glm::mat4>> modelsMatrices;
    void LoadModels(const std::string &models);
    void LoadModelsMatrices(const std::string &modelsMatrices);
public:
    explicit Scene(const std::string &path);
    ~Scene();
    Camera *GetCamera() const;
    void Render(Shader *shader) const;
};
