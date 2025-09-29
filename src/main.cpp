#include "Engine/Engine.h"

int main() {
    const auto RatRacingEngine = new Engine();
    RatRacingEngine->Run();
    delete RatRacingEngine;
    return 0;
}
