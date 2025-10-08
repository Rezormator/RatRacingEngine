#pragma once
#include <string>
#include <vector>

namespace UIPresenter {
    void Initialize();
    void NewImGuiFrame();
    void ProjectSelectionMenu(const std::vector<std::string> &projects);
    void EditProjectMenu();
    void Render();
}
