#include "Project.h"
#include <filesystem>
#include <fstream>
#include "../../Error/Error.h"
#include "../../Resources/Resources.h"
#include "../UI/UIPresenter.h"
#include "../../GameObject/Components/Light/DirectionalLight/DirectionalLight.h"

Project::Project(const std::string &directory)
    : directory(directory), scenesDirectory(directory + "/scenes"), currentSceneIndex(UNINITIALIZED) {
    LoadShader();
    LoadModels();
    if (GetSceneCount() == 0) {
        CreateScene("scene-1");
    }
    LoadScenes();

}

void Project::LoadShader() {
    shader = new Shader("../src/Shader/Shaders/default.vert", "../src/Shader/Shaders/default.frag");
    shader->Bind();
    const auto directionalLight = new DirectionalLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f),
                                                        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.5f));
    directionalLight->Render(shader);
}

void Project::LoadModels() const {
    std::vector<std::string> modelDirectories;
    for (const auto& entry : std::filesystem::directory_iterator(directory + "/models")) {
        if (entry.is_directory()) {
            Resources::LoadModel(entry.path().string());
        }
    }
}

void Project::LoadScenes() {
    for (const auto &entry : std::filesystem::directory_iterator(scenesDirectory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            scenes.push_back(new Scene(entry.path().string()));
        }
    }
    currentSceneIndex = 0;
}

void Project::CreateScene(const std::string &name) const {
    std::ofstream (scenesDirectory + '/' + name + ".json");
}

int Project::GetSceneCount() const {
    int sceneCount = 0;
    for (const auto& entry : std::filesystem::directory_iterator(scenesDirectory)) {
        if (is_regular_file(entry) && entry.path().extension() == ".json") {
            sceneCount++;
        }
    }
    return sceneCount;
}

void Project::SaveProject() const {
    for (const auto scene : scenes) {
        std::ofstream sceneFile(scenesDirectory + '/' + scene->GetName() + ".json");
        sceneFile << scene->GetJson().dump(4);
        sceneFile.close();
    }
}

void Project::Run() const {
    scenes[currentSceneIndex]->Render(shader);
    UIPresenter::EditProjectMenu();
}

void Project::Dispose() {
    for (const auto scene : scenes) {
        scene->Dispose();
        delete scene;
    }
    shader->Dispose();
    delete shader;
}
