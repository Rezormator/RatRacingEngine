#pragma once
#include <vector>
#include "Project/Scene/Scene.h"
#include "UI/UIPresenter.h"

namespace Engine {
    void Initialize();
    void Run();
    void Shut();
    void SetCurrentProjectIndex(int projectIndex);
    void LoadCurrentProject();
}
