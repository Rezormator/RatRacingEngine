#include "Error.h"
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Core/Core.h"

namespace Error {
    void LogError(const std::vector<std::string>& errors, const bool closeAfterError) {
        std::cerr << "Error";
        for (const auto& error : errors) {
            std::cerr << " > " << error;
        }
        std::cerr << std::endl;

        if (closeAfterError) {
            glfwSetWindowShouldClose(Core::GetWindow(), GLFW_TRUE);
        }
    }
}
