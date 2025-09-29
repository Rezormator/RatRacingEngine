#include "Core.h"
#include "../Error/Error.h"

namespace Core {
    GLFWwindow* window;
    int windowWidth;
    int windowHeight;

    void Initialize(const int width, const int height, const char *title, const bool fullscreen) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        CreateWindow(width, height, title, fullscreen);
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            Error::LogError(std::vector<std::string>{"Failed to initialize", "GLAD"});
        }
    }

    void CreateWindow(const int width, const int height, const char *title, const bool fullscreen) {
        GLFWmonitor *monitor = nullptr;

        if (fullscreen) {
            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *monitorProperties = glfwGetVideoMode(monitor);
            windowWidth = monitorProperties->width;
            windowHeight = monitorProperties->height;
        }
        else {
            windowWidth = width;
            windowHeight = height;
        }

        window = glfwCreateWindow(windowWidth, windowHeight, title, monitor, nullptr);

        if (window == nullptr) {
            Error::LogError(std::vector<std::string>{"Failed to create", "GLFW window"});
            glfwTerminate();
        }
    }

    GLFWwindow *GetWindow() {
        return window;
    }

    int GetWindowWidth() {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        return windowWidth;
    }

    int GetWindowHeight() {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        return windowHeight;
    }

    float GetAspectRatio() {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        return static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    }

    void Dispose() {
        glfwTerminate();
    }
}