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

static constexpr usize meshSubdivision = 4;
static constexpr usize meshStep = gridSize / meshSubdivision;
static constexpr usize meshWidth = gridWidth * meshSubdivision;
static constexpr usize meshHeight = gridHeight * meshSubdivision;

struct Tile {
    enum class Kind {
        Insulator,
        Thermostat,
        Conductor,
    };

    static Tile Thermostat(u8 temp) { return {Kind::Thermostat, temp}; }

    static Tile Conductor(u8 temp) { return {Kind::Conductor, temp}; }

    static Tile Insulator() { return {Kind::Insulator, 0}; }

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

        for (usize col = 0; col < meshWidth; ++col) {
            for (usize row = 0; row < meshHeight; ++row) {
                const float x =
                    static_cast<float>(col + row) / (meshHeight + meshWidth);
                DrawRectangle(col * meshStep, row * meshStep, meshStep,
                              meshStep, cmap.get(x).opaque());
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
