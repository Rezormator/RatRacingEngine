#pragma once
#include <vector>
#include "Scene/Scene.h"

class Project {
private:
    std::string directory;
    std::vector<Scene> scenes;
    int currentSceneIndex;
    void LoadModels() const;
    // bool IsValidProject(const std::string &directory);
public:
    explicit Project(std::string directory);
    NODISCARD int GetSceneCount() const;
};
