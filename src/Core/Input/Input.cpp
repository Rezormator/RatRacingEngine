#include "Input.h"
#include <GLFW/glfw3.h>
#include "../Core.h"
#include <iostream>

namespace Input {
    bool firstMove = true;
    double prevXPos;
    double prevYPos;
    float xOffset;
    float yOffset;

    bool GetKeyDown(const int key) {
        return glfwGetKey(Core::GetWindow(), key) == GLFW_TRUE;
    }

    bool GetMouesButtonDown(const int mouseButton) {
        return glfwGetMouseButton(Core::GetWindow(), mouseButton) == GLFW_TRUE;
    }

    float GetXOffset() {
        return xOffset;
    }

    float GetYOffset() {
        return yOffset;
    }

    void CalcCursorOffset() {
        // if (!GetMouesButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
        //     return;
        // }
        double xPos, yPos;
        glfwGetCursorPos(Core::GetWindow(), &xPos, &yPos);
        xOffset = static_cast<float>(xPos - prevXPos);
        yOffset = static_cast<float>(prevYPos - yPos);
        prevXPos = xPos;
        prevYPos = yPos;
    }

    void Update() {
        CalcCursorOffset();
    }
}
