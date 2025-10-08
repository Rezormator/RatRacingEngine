#pragma once
#include <vector>
#include "Scene/Scene.h"

class Project : IDisposable {
private:
    std::string directory;
    std::string scenesDirectory;
    Shader *shader;
    std::vector<Scene *> scenes;
    int currentSceneIndex;
    void LoadShader();
    void LoadModels() const;
    void LoadScenes();
public:
    explicit Project(const std::string &directory);
    NODISCARD int GetSceneCount() const;
    void Run() const;
    void CreateScene(const std::string &name) const;
    void SaveProject() const;
    void Dispose() override;
};
