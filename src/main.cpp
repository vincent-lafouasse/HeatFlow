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
            const float horizontalAdvancement =
                static_cast<float>(col) / gridWidth;

            for (usize row = 0; row < gridHeight; ++row) {
                const float x = (row % 2) ? horizontalAdvancement
                                          : 1.0f - horizontalAdvancement;
                DrawRectangle(col * gridSize, row * gridSize, gridSize,
                              gridSize, cmap.get(x).opaque());
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
