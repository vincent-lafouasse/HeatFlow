#include <raylib.h>
#include <cstdint>

#include "ColorMap.hpp"
#include "Rgb.hpp"

static constexpr int targetFps = 60;

static constexpr usize gridSize = 64;
static constexpr usize gridWidth = 15;
static constexpr usize gridHeight = 10;

static constexpr int screenWidth = gridWidth * gridSize;
static constexpr int screenHeight = gridHeight * gridSize;

static constexpr usize gridSubdivision = 4;
static constexpr usize gridStep = gridSize / gridSubdivision;
static constexpr usize width = gridWidth * gridSubdivision;
static constexpr usize height = gridHeight * gridSubdivision;

struct Tile {
    enum class Kind {
        Thermostat,
        Conductor,
        Insulator,
    };

    Kind kind;
    uint8_t temperature;
    /* uint8_t conductivity; */
};

struct Grid {
    std::array<std::array<Tile, gridWidth>, gridHeight> tiles;
};

int main() {
    InitWindow(screenWidth, screenHeight, "hi");
    SetTargetFPS(targetFps);

    const ColorMap cmap = ColorMap::Viridis();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(catpuccin::DarkGray.opaque());

        for (usize col = 0; col < width; ++col) {
            for (usize row = 0; row < height; ++row) {
                const float x =
                    static_cast<float>(col + row) / (height + width);
                DrawRectangle(col * gridStep, row * gridStep, gridStep,
                              gridStep, cmap.get(x).opaque());
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
