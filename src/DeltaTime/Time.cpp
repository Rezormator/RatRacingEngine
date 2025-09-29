#include "Time.h"
#include <GLFW/glfw3.h>

namespace Time {
    float previousTime = 0.0f;
    float deltaTime;

    void UpdateDeltaTime() {
        const auto currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;
    }

    float GetDeltaTime() {
        return deltaTime;
    }
}
