#include <raylib.h>

#include "ColorMap.hpp"
#include "Rgb.hpp"

static constexpr int targetFps = 60;

static constexpr usize gridMagnitude = 6;
static constexpr usize gridSize = (1 << gridMagnitude);  // 64px per big cell
static constexpr usize gridSubdivision = 4;              // cut tiles in 16
static constexpr usize gridStep =
    gridSize / gridSubdivision;  // 16px per sub-cell

static constexpr usize bigGridWidth = 15;
static constexpr usize bigGridHeight = 10;
static constexpr usize gridWidth = bigGridWidth * gridSubdivision;
static constexpr usize gridHeight = bigGridHeight * gridSubdivision;

static constexpr int width = gridWidth * gridStep;
static constexpr int height = gridHeight * gridStep;

int main() {
    InitWindow(width, height, "hi");
    SetTargetFPS(targetFps);

    const ColorMap cmap = ColorMap::Inferno();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(catpuccin::DarkGray.opaque());

        for (usize col = 0; col < gridWidth; ++col) {
            const float horizontalAdvancement =
                static_cast<float>(col) / gridWidth * gridSubdivision;

            for (usize row = 0; row < gridHeight; ++row) {
                DrawRectangle(col * gridStep, row * gridStep, gridStep,
                              gridStep,
                              cmap.get(horizontalAdvancement).opaque());
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
