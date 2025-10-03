#include "Engine.h"
#include <filesystem>
#include <imgui.h>
#include "../Core/Core.h"
#include "../Core/Input/Input.h"
#include "../Core/Time/Time.h"
#include "../Shader/Shader.h"
// #include "../GameObject/Components/Light/DirectionalLight/DirectionalLight.h"
// #include "../GameObject/Components/Light/PointLight/PointLight.h"
// #include "../GameObject/Components/Light/SpotLight/SpotLight.h"
// #include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include "imgui/backends/imgui_impl_opengl3.h"
#include <fstream>

#include "Project/Project.h"

namespace Engine {
    constexpr auto PROJECTS_DIRECTORY = "../projects";
    std::vector<Project*> projects;
    int currentProjectIndex = -1;

    void Initialize() {
        // !!!!!!!!!
        Core::Initialize();
        UserInterface::Initialize();
        // LoadScenes();
        // currentScene = 0;
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(Core::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    // void Engine::SetCurrentProjectIndex(const int projectIndex) {
    //     currentProjectIndex = projectIndex;
    // }

    // void Engine::LoadScenes() {
    //     for (const auto &entry: std::filesystem::directory_iterator(PATH_TO_SCENES)) {
    //         scenes.push_back(new Scene(entry.path().string()));
    //     }
    // }

    void Run() {
        // glfwSetInputMode(Core::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        const auto shader = new Shader("../src/Shader/Shaders/default.vert",
                                       "../src/Shader/Shaders/default.frag");
        shader->Bind();
        // shader->SetVec3("directionalLights[0].direction", glm::vec3(0.0f, 1.0f, 0.5f));
        // shader->SetVec3("directionalLights[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        // shader->SetVec3("directionalLights[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        // shader->SetVec3("directionalLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        //
        // const auto directionalLight = new DirectionalLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f),
        //                                             glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.5f));
        // directionalLight->Render(shader);
        //
        // const auto pointLight = new PointLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f),
        //                                             glm::vec3(1.0f, 1.0f, 1.0f), 3, 0.5, glm::vec3(0.0f, 0.0f, 3.0f));
        // pointLight->Render(shader);
        //
        // const auto spotLight = new SpotLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f),
        //                                     glm::vec3(1.0f, 1.0f, 1.0f), 10, 0.5, 10, 15, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        // spotLight->Render(shader);

        while (!glfwWindowShouldClose(Core::GetWindow())) {
            Input::Update();
            Time::UpdateDeltaTime();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 🔹 Початок нового кадру ImGui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 🔹 Твоє меню
            if (currentProjectIndex == -1) {
                UserInterface::ProjectSelectionMenu();
            }
            // scenes[currentScene]->Render(shader);
            // userInterface->Render();

            // 🔹 Рендеринг ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(Core::GetWindow());
            glfwPollEvents();
        }
        delete shader;
    }

    void CreateProject(const std::string &directory) {
        std::ofstream project(directory);
        std::ofstream models(directory + "/models");
        std::ofstream scenes(directory + "/scenes");
    }

    void LoadProject(const std::string &directory) {
        projects.push_back(new Project(directory));
    }

    // TODO : remove project method
    // void RemoveProject(const std::string &directory) {
    //     std::filesystem::remove(directory);
    // }

    // TODO : is valid project method

    // TODO : shut method
    void Shut() {
    }
}
