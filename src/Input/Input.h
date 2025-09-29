#pragma once
#include "../Utils/Utils.h"

namespace Input {
    bool GetKeyDown(int key);
    bool GetMouesButtonDown(int mouseButton);
    void CalcCursorOffset();
    NODISCARD float GetXOffset();
    NODISCARD float GetYOffset();
    void Update();
}
