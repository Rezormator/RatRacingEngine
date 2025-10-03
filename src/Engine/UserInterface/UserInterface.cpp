#include "UserInterface.h"
#include <vector>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include "imgui/backends/imgui_impl_opengl3.h"
#include "../../Core/Core.h"

namespace UserInterface {
    void Initialize() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        const ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(Core::GetWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    struct Project {
        std::string name;
        std::string path;
        std::string initials;
    };

    static std::pmr::vector<Project> projects = {
        {"RatRacingEngine", "../projects/RatRacingEngine", "FD"},
        {"Sandbox", "../projects/Sandbox", "AS"},
        {"TestGame", "../projects/TestGame", "AS"}
    };

    void ProjectSelectionMenu() {
        // Повноекранне вікно
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Project Selector", nullptr,
                     ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove);

        // 🔍 Пошукове поле
        static char searchBuf[128] = "";
        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - 200); // залишає місце під кнопки
        ImGui::InputTextWithHint("##search", "Search projects", searchBuf, IM_ARRAYSIZE(searchBuf));
        ImGui::PopItemWidth();

        ImGui::SameLine();
        if (ImGui::Button("Create project")) {
            // TODO: create project
        }
        ImGui::SameLine();
        if (ImGui::Button("Open project")) {
            // TODO: open project
        }

        ImGui::Separator();

        // 📂 Список проєктів
        for (size_t i = 0; i < projects.size(); i++) {
            auto &p = projects[i];

            // Фейковий "бейдж" з ініціалами
            ImGui::PushID(static_cast<int>(i));
            ImGui::BeginGroup();
            ImGui::Button(p.initials.c_str(), ImVec2(40, 40)); // прямокутник з літерами
            ImGui::SameLine();
            if (ImGui::Selectable(p.name.c_str(), false)) {
                // TODO: відкрити проєкт
            }
            ImGui::EndGroup();
            ImGui::PopID();
        }

        ImGui::End();
    }

}
