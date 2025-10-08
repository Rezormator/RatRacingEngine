#include "Engine.h"
#include <filesystem>
#include <imgui.h>
#include "../Core/Core.h"
#include "../Core/Input/Input.h"
#include "../Core/Time/Time.h"
#include "../Shader/Shader.h"
#include "../GameObject/Components/Light/DirectionalLight/DirectionalLight.h"
// #include "../GameObject/Components/Light/PointLight/PointLight.h"
// #include "../GameObject/Components/Light/SpotLight/SpotLight.h"
// #include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include "imgui/backends/imgui_impl_opengl3.h"
#include <fstream>

#include "Project/Project.h"

namespace Engine {
    constexpr auto PROJECTS_DIRECTORY = "../projects";
    std::vector<std::string> projects;
    Project* project;
    int currentProjectIndex = UNINITIALIZED;

    std::vector<std::string> GetProjectsNames() {
        std::vector<std::string> projectsNames;
        for (const auto& entry : std::filesystem::directory_iterator(PROJECTS_DIRECTORY)) {
            if (is_directory(entry)) {
                projectsNames.push_back(entry.path().string());
            }
        }
        return projectsNames;
    }

    void SetCurrentProjectIndex(const int projectIndex) {
        currentProjectIndex = projectIndex;
    }

    void Initialize() {
        // !!!!!!!!!
        Core::Initialize();
        UIPresenter::Initialize();
        Input::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        projects = GetProjectsNames();
        glEnable(GL_DEPTH_TEST);
        // LoadScenes();
        // currentScene = 0;
    }

    void Run() {
        // glfwSetInputMode(Core::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // shader->SetVec3("directionalLights[0].direction", glm::vec3(0.0f, 1.0f, 0.5f));
        // shader->SetVec3("directionalLights[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        // shader->SetVec3("directionalLights[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        // shader->SetVec3("directionalLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        //
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
            Core::NewFrame();
            UIPresenter::NewImGuiFrame();

            if (currentProjectIndex == UNINITIALIZED) {
                UIPresenter::ProjectSelectionMenu(GetProjectsNames());
            }
            else {
                project->Run();
            }

            UIPresenter::Render();
            glfwSwapBuffers(Core::GetWindow());
            glfwPollEvents();
        }
    }

    // TODO: shut method
    void Shut() {
    }

    void CreateProject(const std::string &directory) {
        std::filesystem::create_directory(directory);
        std::filesystem::create_directory(directory + "/models");
        std::filesystem::create_directory(directory + "/scenes");
    }

    void LoadCurrentProject() {
        project = new Project(projects[currentProjectIndex]);
        Input::SetCursorMode(CursorMode::SCENE_VIEW);
    }

    // TODO: remove project method
    // void RemoveProject(const std::string &directory) {
    //     std::filesystem::remove(directory);
    // }

    // TODO: is valid project method

}
