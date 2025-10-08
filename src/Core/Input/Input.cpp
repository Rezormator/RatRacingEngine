#include "Input.h"
#include <GLFW/glfw3.h>
#include "../Core.h"
#include <iostream>

#include "../Screen.h"

namespace Input {
    bool firstMove = true;
    double prevXPos = 0.0;
    double prevYPos = 0.0;
    float xOffset = 0.0f;
    float yOffset = 0.0f;
    CursorMode currentMode = CursorMode::UI;

    void SetCursorMode(const CursorMode mode) {
        currentMode = mode;
        glfwSetInputMode(Core::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    bool GetKeyDown(const int key) {
        return glfwGetKey(Core::GetWindow(), key) == GLFW_PRESS;
    }

    bool GetMouseButtonDown(const int mouseButton) {
        return glfwGetMouseButton(Core::GetWindow(), mouseButton) == GLFW_PRESS;
    }

    float GetXOffset() {
        return xOffset;
    }

    float GetYOffset() {
        return yOffset;
    }

    void CalcCursorOffset() {
        double xPos, yPos;
        glfwGetCursorPos(Core::GetWindow(), &xPos, &yPos);

        xOffset = 0.0f;
        yOffset = 0.0f;

        if (currentMode == CursorMode::UI) {
            prevXPos = xPos;
            prevYPos = yPos;
            return;
        }

        auto [x, y, width, height] = Core::GetViewport();
        if (!(xPos >= x && xPos <= x + width && yPos >= y && yPos <= y + height)) {
            firstMove = true;
            return;
        }

        if (!GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            firstMove = true;
            return;
        }

        if (firstMove) {
            prevXPos = xPos;
            prevYPos = yPos;
            firstMove = false;
            return;
        }

        xOffset = static_cast<float>(xPos - prevXPos);
        yOffset = static_cast<float>(prevYPos - yPos);

        prevXPos = xPos;
        prevYPos = yPos;
    }

    void SetInputMode(const int mode, const int value) {
        glfwSetInputMode(Core::GetWindow(), mode, value);
    }

    void Update() {
        CalcCursorOffset();

        if (GetKeyDown(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(Core::GetWindow(), GLFW_TRUE);
        }
    }
}
