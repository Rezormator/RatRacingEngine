#include "Project.h"
#include <filesystem>
#include <fstream>
#include <utility>
#include "../../Resources/Resources.h"

Project::Project(std::string directory) : directory(std::move(directory)), currentSceneIndex(UNINITIALIZED) {
    LoadModels();
}

void Project::LoadProject() {
    LoadModels();
    if (GetSceneCount() == 0) {
        std::ofstream scenes(directory + "/scenes/scene-1");
    }
}

void Project::LoadModels() const {
    std::vector<std::string> modelDirectories;
    for (const auto& entry : std::filesystem::directory_iterator(directory + "/models")) {
        if (entry.is_regular_file()) {
            Resources::LoadModel(entry.path().string());
        }
    }
}

int Project::GetSceneCount() const {
    int sceneCount = 0;
    for (const auto& entry : std::filesystem::directory_iterator(directory + "/scenes")) {
        if (is_regular_file(entry)) {
            sceneCount++;
        }
    }
    return sceneCount;
}

