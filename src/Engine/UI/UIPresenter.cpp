#include "UIPresenter.h"
#include <vector>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include "../Engine.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "../../Core/Core.h"

namespace UIPresenter {
    constexpr auto MENU_COLOR = ImVec4(0.145f, 0.145f, 0.149f, 1.0f);
    constexpr auto HOVER_PROJECT_COLOR = ImVec4(0.2745f, 0.2902f, 0.3020f, 1.0f);
    const std::vector colors{
        ImVec4(0.9961f, 0.7529f, 0.0235f, 1.0f),
        ImVec4(0.2941f, 0.6824f, 0.3098f, 1.0f),
        ImVec4(0.1255f, 0.5843f, 0.9490f, 1.0f),
        ImVec4(0.9098f, 0.1137f, 0.3843f, 1.0f),
        ImVec4(0.9961f, 0.5922f, 0.0f, 1.0f),
        ImVec4(0.5412f, 0.7608f, 0.2863f, 1.0f),
        ImVec4(0.0078f, 0.6588f, 0.9529f, 1.0f),
        ImVec4(0.6078f, 0.1490f, 0.6863f, 1.0f)
    };

    void Initialize() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        const ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(Core::GetWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void NewImGuiFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ProjectSelectionMenu(const std::vector<std::string> &projects) {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, MENU_COLOR);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Project Selector", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        for (size_t i = 0; i < projects.size(); i++) {
            const auto name = std::filesystem::path(projects[i]).filename().string();
            ImGui::PushID(static_cast<int>(i));

            constexpr float padding = 20.0f;
            constexpr float iconSize = 30.0f;

            constexpr float rowHeight = 70.0f;
            const float rowWidth = ImGui::GetContentRegionAvail().x;

            ImVec2 cursorScreenPosStart = ImGui::GetCursorScreenPos();
            ImGui::InvisibleButton("row_bg", ImVec2(rowWidth, rowHeight));

            if (ImGui::IsItemHovered()) {
                ImGui::GetWindowDrawList()->AddRectFilled(
                    cursorScreenPosStart,
                    ImVec2(cursorScreenPosStart.x + rowWidth, cursorScreenPosStart.y + rowHeight),
                    ImGui::GetColorU32(HOVER_PROJECT_COLOR));
            }

            ImVec2 iconRectMin = ImVec2(cursorScreenPosStart.x + padding, cursorScreenPosStart.y + (rowHeight - iconSize) * 0.5f);
            ImVec2 iconRectMax = ImVec2(iconRectMin.x + iconSize, iconRectMin.y + iconSize);

            const ImU32 iconBgColor = ImGui::GetColorU32(colors[i % colors.size()]);
            ImGui::GetWindowDrawList()->AddRectFilled(iconRectMin, iconRectMax, iconBgColor, 5.0f);

            std::string iconText = Utils::GetTwoLetters(name);
            const ImVec2 iconTextSize = ImGui::CalcTextSize(iconText.c_str());
            ImVec2 iconTextPos = ImVec2(iconRectMin.x + (iconSize - iconTextSize.x) * 0.5f, iconRectMin.y + (iconSize - iconTextSize.y) * 0.5f);
            ImGui::GetWindowDrawList()->AddText(iconTextPos, ImGui::GetColorU32(ImGuiCol_Text), iconText.c_str());

            ImVec2 textPos;
            textPos.x = cursorScreenPosStart.x + rowHeight;
            textPos.y = cursorScreenPosStart.y + (rowHeight - ImGui::CalcTextSize(name.c_str()).y) * 0.5f;

            ImGui::GetWindowDrawList()->AddText(
                textPos,
                ImGui::GetColorU32(ImGuiCol_Text),
                name.c_str()
            );

            if (ImGui::IsItemClicked()) {
                Engine::SetCurrentProjectIndex(static_cast<int>(i));
                Engine::LoadCurrentProject();
            }

            ImGui::PopID();
        }

        ImGui::End();
        ImGui::PopStyleColor();
    }

    void DrawRectangle(const ImVec2 position, const float x, const float y, const ImVec4 leftColor, const ImVec4 rightColor) {
        ImGui::GetWindowDrawList()->AddRectFilledMultiColor(
            position,
            ImVec2(x, y),
            ImGui::GetColorU32(leftColor),
            ImGui::GetColorU32(rightColor),
            ImGui::GetColorU32(rightColor),
            ImGui::GetColorU32(leftColor)
            );
    }

    void DrawDefaultPanel(const std::string &name, ImVec2 position, ImVec2 size) {
        ImGui::SetNextWindowPos(position);
        ImGui::SetNextWindowSize(size);
        ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        position = ImGui::GetWindowPos();
        size = ImGui::GetWindowSize();
        DrawRectangle(position, position.x + size.x, position.y + size.y, ImVec4(0.158f, 0.158f, 0.158f, 1.0f), ImVec4(0.1765f, 0.1765f, 0.1765f, 1.0f));
        DrawRectangle(position, position.x + size.x, position.y + 30.0f, ImVec4(0.090f, 0.082f, 0.078f, 1.0f), ImVec4(0.129f, 0.129f, 0.129f, 1.0f));
        ImGui::Text(name.c_str());
        ImGui::End();
    }

    void EditProjectMenu() {
        const ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        constexpr float panelSizeValue = 200.0f;
        Core::SetViewport(0, panelSizeValue, displaySize.x - panelSizeValue * 2, displaySize.y - panelSizeValue);
        ImGui::GetStyle().WindowBorderSize = 0.0f;
        DrawDefaultPanel("Scene", ImVec2(displaySize.x - panelSizeValue * 2, 0), ImVec2(panelSizeValue, displaySize.y - panelSizeValue));
        DrawDefaultPanel("Inspector", ImVec2(displaySize.x - panelSizeValue, 0), ImVec2(panelSizeValue, displaySize.y - panelSizeValue));
        DrawDefaultPanel("Project", ImVec2(0, displaySize.y - panelSizeValue), ImVec2(displaySize.x - panelSizeValue * 2, panelSizeValue));
        DrawDefaultPanel("Console", ImVec2(displaySize.x - panelSizeValue * 2, displaySize.y - panelSizeValue), ImVec2(panelSizeValue * 2, panelSizeValue));
    }
}
