#include "Scene.h"
#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "../../../Core/Time/Time.h"
#include "../../../Core/Input/Input.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "../../../Core/Core.h"

Scene::Scene(const std::string &path) {
    LoadModels(Utils::ReadTextFromFile(path + "/models"));
    LoadModelsMatrices(Utils::ReadTextFromFile(path + "/matrices"));
    camera = new Camera();
}

void Scene::LoadModels(const std::string &models) {
    std::vector<std::string> modelsPaths;
    {
        std::istringstream iss(models);
        std::string line;
        while (std::getline(iss, line)) {
            modelsPaths.push_back(std::move(line));
        }
    }
    for (const auto& line : modelsPaths) {
        std::istringstream iss(line);
        std::string path;
        GLuint id;
        iss >> path >> id;
        // this->models[id] = new Model(path.data());
    }
}

void Scene::LoadModelsMatrices(const std::string &modelsMatrices) {
    std::istringstream stream(modelsMatrices);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.empty()) continue;

        std::istringstream idStream(line);
        GLuint id;
        idStream >> id;

        glm::mat4 model;
        if (std::getline(stream, line)) {
            std::istringstream matStream(line);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    matStream >> model[i][j];
                }
            }
        }

        // this->modelsMatrices.emplace_back(id, model);
    }
}

Camera* Scene::GetCamera() const {
    return camera;
}

void Scene::Render(Shader *shader) const {
    Input::Update();
    Time::UpdateDeltaTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->Update();
    camera->Render(shader);

    // for (const auto&[id, modelMatrix] : modelsMatrices) {
    //     const auto model = models.at(id);
    //     model->SetModel(modelMatrix);
    //     model->Render(shader);
    // }

    glfwSwapBuffers(Core::GetWindow());
    glfwPollEvents();
}

void Scene::Dispose() {
    delete camera;
}
