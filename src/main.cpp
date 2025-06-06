#include <raylib.h>

#include "ColorMap.hpp"
#include "Rgb.hpp"

static constexpr int width = 1600;
static constexpr int height = 900;
static constexpr int targetFps = 140;

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    const ColorMap cmap = ColorMap::Viridis();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(catpuccin::DarkGray.opaque());
        constexpr usize nSteps = 200;
        constexpr int step = width / nSteps;

        for (usize i = 0; i < nSteps; ++i) {
            const float x = static_cast<float>(i) / nSteps;
            DrawRectangle(i * step, 0, step, height, cmap.get(x).opaque());
        }

        EndDrawing();
    }

    CloseWindow();
}
