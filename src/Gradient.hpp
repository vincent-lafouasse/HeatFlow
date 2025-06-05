#pragma once

#include <array>
#include <cmath>

#include "Rgb.hpp"

static u8 u8FromFloat(float x) {
    if (x > 255.0f) {
        return 255;
    } else if (x < 0.0f) {
        return 0;
    } else {
        return static_cast<u8>(std::trunc(x));
    }
}

static u8 lerpU8(u8 start, u8 end, float x) {
    const float asFloat =
        static_cast<float>(start) * (1.0f - x) + static_cast<float>(end) * x;
    return u8FromFloat(asFloat);
}

static Rgb lerpRgb(Rgb start, Rgb end, float x) {
    return {
        lerpU8(start.red, end.red, x),
        lerpU8(start.green, end.green, x),
        lerpU8(start.blue, end.blue, x),
    };
}

class Gradient {
   public:
    [[nodiscard]] static Rgb get(float x) {
        const float floatIndex = x * (colors.size() - 1);
        const usize index = static_cast<usize>(std::trunc(floatIndex));
        const float offset = floatIndex - index;
        const Rgb low = colors[index];
        const Rgb high = colors[index + 1];
        return lerpRgb(low, high, offset);
    }

   private:
    static constexpr std::array<Rgb, 9> colors{
        catpuccin::Red,    catpuccin::Maroon,   catpuccin::Peach,
        catpuccin::Yellow, catpuccin::Green,    catpuccin::Teal,
        catpuccin::Sky,    catpuccin::Sapphire, catpuccin::Blue,
    };
};
