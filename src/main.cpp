#include <raylib.h>
#include <cassert>
#include <cstdint>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ColorMap.hpp"
#include "Rgb.hpp"

static constexpr int targetFps = 60;

static constexpr usize gridSize = 64;
static constexpr usize gridWidth = 15;
static constexpr usize gridHeight = 10;

static constexpr int screenWidth = gridWidth * gridSize;
static constexpr int scalePanelHeight = 64;
static constexpr int screenHeight = gridHeight * gridSize + scalePanelHeight;

static constexpr usize meshSubdivision = 4;
static constexpr usize meshStep = gridSize / meshSubdivision;
static constexpr usize meshWidth = gridWidth * meshSubdivision;
static constexpr usize meshHeight = gridHeight * meshSubdivision;

struct Look {
    ColorMap cmap;
    bool displayFps;
};

struct Tile {
    enum class Kind {
        Insulator,
        Conductor,
        /* Thermostat, */
    };

    /* static Tile Thermostat(u8 temp) { return {Kind::Thermostat, temp}; } */

    static Tile Conductor(float temp) { return {Kind::Conductor, temp}; }

    static Tile Insulator() { return {Kind::Insulator, 0}; }

    bool conducts() const { return kind == Kind::Conductor; }

    Kind kind;
    float temperature;
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

    void drawScaleBar(const Look& look) const {
        static constexpr int nSteps = 120;
        static constexpr int scaleBarStep = screenWidth / nSteps;

        for (int i = 0; i < nSteps; ++i) {
            const float x = static_cast<float>(i) / (nSteps - 1);
            DrawRectangle(i * scaleBarStep, gridHeight * gridSize, scaleBarStep,
                          scalePanelHeight, look.cmap.get(x).opaque());
        }
    }

    void render(const Look& look) const {
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
                                  gridSize, look.cmap.get(temp).opaque());
                }
            }
        }

        if (look.displayFps) {
            DrawFPS(0, 0);
        }

        this->drawScaleBar(look);

        EndDrawing();
    }

    Grid(const std::vector<std::vector<Tile>>& t) : tiles(t), laplacian() {
        for (usize col = 0; col < gridWidth; ++col) {
            std::vector<float> line(gridWidth, 0);
            laplacian.push_back(line);
        }
    }

    void computeLaplacian() {
        for (usize col = 0; col < gridWidth; ++col) {
            for (usize row = 0; row < gridHeight; ++row) {
                laplacian[row][col] = computeLaplacianAt(col, row);
            }
        }
    }

    void update() {
        computeLaplacian();
        constexpr float conductivity = 1.0f;
        constexpr float dt = 0.1f;

        for (usize col = 0; col < gridWidth; ++col) {
            for (usize row = 0; row < gridHeight; ++row) {
                Tile& tile = tiles[row][col];

                if (tile.conducts()) {
                    tile.temperature += conductivity * laplacian[row][col] * dt;
                }
            }
        }
    }

    float computeLaplacianAt(usize col, usize row) {
        if (!tiles[row][col].conducts()) {
            return -1.0f;
        }

        const int col__ = static_cast<int>(col);
        const int row__ = static_cast<int>(row);

        std::pair<int, int> candidate1 = std::make_pair(col__, row__ + 1);
        std::pair<int, int> candidate2 = std::make_pair(col__, row__ - 1);
        std::pair<int, int> candidate3 = std::make_pair(col__ + 1, row__);
        std::pair<int, int> candidate4 = std::make_pair(col__ - 1, row__);

        auto temp = [&](const std::pair<int, int>& candidate) {
            if (candidate.first < 0 ||
                candidate.first > static_cast<int>(gridWidth)) {
                return -1.0f;
            }
            if (candidate.second < 0 ||
                candidate.second > static_cast<int>(gridHeight)) {
                return -1.0f;
            }

            return tiles[candidate.second][candidate.first].temperature;
        };

        usize count = 0;
        float mean = 0.0f;

        float temperature;
        temperature = temp(candidate1);
        if (temperature >= 0.0f) {
            ++count;
            mean += temperature;
        }
        temperature = temp(candidate2);
        if (temperature >= 0.0f) {
            ++count;
            mean += temperature;
        }
        temperature = temp(candidate3);
        if (temperature >= 0.0f) {
            ++count;
            mean += temperature;
        }
        temperature = temp(candidate4);
        if (temperature >= 0.0f) {
            ++count;
            mean += temperature;
        }

        if (count == 0) {
            return 0.0f;
        } else {
            return (mean / count) - tiles[row][col].temperature;
        }
    }

    std::vector<std::vector<Tile>> tiles;
    std::vector<std::vector<float>> laplacian;
};

int main() {
    InitWindow(screenWidth, screenHeight, "hi");
    SetTargetFPS(targetFps);

    Grid grid = Grid::funnel();
    Look look = {
        .cmap = ColorMap::Viridis(),
        .displayFps = true,
    };

    std::unordered_set<int> keys;

    while (!WindowShouldClose()) {
        constexpr int space = KEY_SPACE;
        if (IsKeyDown(space) && !keys.contains(space)) {
            look.displayFps = !look.displayFps;
            keys.insert(space);
        } else if (IsKeyUp(KEY_SPACE) && keys.contains(space)) {
            keys.erase(space);
        }

        grid.update();
        grid.render(look);
    }

    CloseWindow();
}
