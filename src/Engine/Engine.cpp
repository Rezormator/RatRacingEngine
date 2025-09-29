#include "Engine.h"
#include <filesystem>
#include <imgui.h>

#include "../Core/Core.h"
#include "../Input/Input.h"
#include "Scene/GameObject/Light/DirectionalLight/DirectionalLight.h"
#include "Scene/GameObject/Light/PointLight/PointLight.h"
#include "Scene/GameObject/Light/SpotLight/SpotLight.h"

Engine::Engine() {
    // !!!!!!!!!
    Core::Initialize();
    LoadScenes();
    currentScene = 0;
    userInterface = new UserInterface();
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(Core::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Engine::~Engine() {
    for (const auto scene: scenes) {
        delete scene;
    }
}

void Engine::LoadScenes() {
    for (const auto &entry: std::filesystem::directory_iterator(PATH_TO_SCENES)) {
        scenes.push_back(new Scene(entry.path().string()));
    }
}

void Engine::Run() const {
    glfwSetInputMode(Core::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    const auto shader = new Shader("../src/Engine/Shader/Shaders/default.vert",
                                   "../src/Engine/Shader/Shaders/default.frag");
    shader->Bind();
    // shader->SetVec3("directionalLights[0].direction", glm::vec3(0.0f, 1.0f, 0.5f));
    // shader->SetVec3("directionalLights[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    // shader->SetVec3("directionalLights[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    // shader->SetVec3("directionalLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));

    const auto directionalLight = new DirectionalLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f),
                                                glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.5f));
    // directionalLight->Render(shader);

    const auto pointLight = new PointLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f),
                                                glm::vec3(1.0f, 1.0f, 1.0f), 3, 0.5, glm::vec3(0.0f, 0.0f, 3.0f));
    pointLight->Render(shader);

    const auto spotLight = new SpotLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f),
                                        glm::vec3(1.0f, 1.0f, 1.0f), 10, 0.5, 10, 15, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    // spotLight->Render(shader);


    while (!glfwWindowShouldClose(Core::GetWindow())) {
        scenes[currentScene]->Render(shader);
        userInterface->Render();
        if (Input::GetKeyDown(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(Core::GetWindow(), GLFW_TRUE);
        }
    }
    delete shader;
}
