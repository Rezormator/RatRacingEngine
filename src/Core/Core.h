#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Utils/Utils.h"

namespace Core {
    constexpr float DEFAULT_SCREEN_WIDTH = 800.0f;
    constexpr float DEFAULT_SCREEN_HEIGHT = 600.0f;
    constexpr auto DEFAULT_WINDOW_TITLE = "OpenGL Example";

    void Initialize(int width = DEFAULT_SCREEN_WIDTH, int height = DEFAULT_SCREEN_HEIGHT,
                    const char *title = DEFAULT_WINDOW_TITLE, bool fullscreen = false);
    void CreateWindow(int width, int height, const char *title, bool fullscreen);
    NODISCARD GLFWwindow *GetWindow();
    NODISCARD int GetWindowWidth();
    NODISCARD int GetWindowHeight();
    NODISCARD float GetAspectRatio();
    void Dispose();
}
