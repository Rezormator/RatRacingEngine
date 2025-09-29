#pragma once
#include <vector>
#include "Scene/Scene.h"
#include "UserInterface/UserInterface.h"

class Engine {
private:
    static constexpr auto *PATH_TO_SCENES = "../resources/scenes/";
    int currentScene;
    std::vector<Scene *> scenes;
    UserInterface *userInterface;
    void LoadScenes();
public:
    Engine();
    ~Engine();
    void Run() const;
};
