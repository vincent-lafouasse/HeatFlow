#include <raylib.h>

#include "ColorMap.hpp"
#include "Rgb.hpp"

static constexpr int targetFps = 60;

static constexpr usize gridSize = 64;
static constexpr usize gridWidth = 15;
static constexpr usize gridHeight = 10;

static constexpr int width = gridWidth * gridSize;
static constexpr int height = gridHeight * gridSize;

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    const ColorMap cmap = ColorMap::Inferno();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(catpuccin::DarkGray.opaque());

        for (usize col = 0; col < gridWidth; ++col) {
            for (usize row = 0; row < gridHeight; ++row) {
                const float x = static_cast<float>(col + row) / (gridHeight + gridWidth);
                DrawRectangle(col * gridSize, row * gridSize, gridSize,
                              gridSize, cmap.get(x).opaque());
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
