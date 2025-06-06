#include <raylib.h>
#include <cassert>
#include <cstdint>
#include <vector>

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
        Conductor,
        /* Thermostat, */
    };

    /* static Tile Thermostat(u8 temp) { return {Kind::Thermostat, temp}; } */

    static Tile Conductor(u8 temp) { return {Kind::Conductor, temp}; }

    static Tile Insulator() { return {Kind::Insulator, 0}; }

    Kind kind;
    uint8_t temperature;
    /* uint8_t conductivity; */
};

static const char* line0 = "###############";
static const char* line1 = "fffff#####00000";
static const char* line2 = "fffff#####00000";
static const char* line3 = "fffff#####00000";
static const char* line4 = "fffff7777700000";
static const char* line5 = "fffff7777700000";
static const char* line6 = "fffff#####00000";
static const char* line7 = "fffff#####00000";
static const char* line8 = "fffff#####00000";
static const char* line9 = "###############";

static bool isHexDigit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

static uint8_t fromHex(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return 10 + c - 'a';
    } else {
        return 0;
    }
}

std::vector<Tile> parseLine(const char* s) {
    std::vector<Tile> line;

    for (; *s; ++s) {
        if (*s == '#') {
            line.push_back(Tile::Insulator());
        } else if (isHexDigit(*s)) {
            line.push_back(Tile::Conductor(fromHex(*s) * 16));
        }
    }

    return line;
}

struct Grid {
    static Grid funnel() {
        auto t0 = parseLine(line0);
        assert(t0.size() == gridWidth);
        auto t1 = parseLine(line1);
        assert(t1.size() == gridWidth);
        auto t2 = parseLine(line2);
        assert(t2.size() == gridWidth);
        auto t3 = parseLine(line3);
        assert(t3.size() == gridWidth);
        auto t4 = parseLine(line4);
        assert(t4.size() == gridWidth);
        auto t5 = parseLine(line5);
        assert(t5.size() == gridWidth);
        auto t6 = parseLine(line6);
        assert(t6.size() == gridWidth);
        auto t7 = parseLine(line7);
        assert(t7.size() == gridWidth);
        auto t8 = parseLine(line8);
        assert(t8.size() == gridWidth);
        auto t9 = parseLine(line9);
        assert(t9.size() == gridWidth);

        std::vector<std::vector<Tile>> tiles{t0, t1, t2, t3, t4,
                                             t5, t6, t7, t8, t9};

        return Grid(tiles);
    }

    void render(const ColorMap& cmap) const {
        BeginDrawing();
        ClearBackground(catpuccin::DarkGray.opaque());

        for (usize col = 0; col < gridWidth; ++col) {
            for (usize row = 0; row < gridHeight; ++row) {
                const Tile tile = tiles[row][col];

                if (tile.kind == Tile::Kind::Insulator) {
                    DrawRectangle(col * gridSize, row * gridSize, gridSize,
                                  gridSize, catpuccin::DarkGray.opaque());
                } else if (tile.kind == Tile::Kind::Conductor) {
                    const float temp = tile.temperature / 255.0f;
                    DrawRectangle(col * gridSize, row * gridSize, gridSize,
                                  gridSize, cmap.get(temp).opaque());
                }
            }
        }

        EndDrawing();
    }

    Grid(const std::vector<std::vector<Tile>>& t) : tiles(t) {}

    std::vector<std::vector<Tile>> tiles;
};

int main() {
    InitWindow(screenWidth, screenHeight, "hi");
    SetTargetFPS(targetFps);

    Grid grid = Grid::funnel();
    const ColorMap cmap = ColorMap::Inferno();

    while (!WindowShouldClose()) {
        grid.render(cmap);
    }

    CloseWindow();
}
