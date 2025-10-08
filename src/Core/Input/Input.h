#pragma once
#include "../../Utils/Utils.h"
#include "InputModes.h"

namespace Input {
    bool GetKeyDown(int key);
    bool GetMouesButtonDown(int mouseButton);
    void CalcCursorOffset();
    void SetInputMode(int mode, int value);
    void SetCursorMode(CursorMode mode);
    NODISCARD float GetXOffset();
    NODISCARD float GetYOffset();
    void Update();
}
