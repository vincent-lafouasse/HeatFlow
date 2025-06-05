#include <raylib.h>

#include "catpuccin.hpp"

static constexpr int width = 1600;
static constexpr int height = 900;
static constexpr int targetFps = 140;

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(catpuccin::lavender.opaque());
        EndDrawing();
    }

    CloseWindow();
}
