#pragma once

#include <array>
#include <cmath>

#include "Rgb.hpp"

u8 lerpU8(u8 start, u8 end, float x) {
    const float asFloat =
        static_cast<float>(start) * (1.0f - x) + static_cast<float>(end) * x;
    return trunc(asFloat) > 255.0f ? 255 : trunc(asFloat);
}

Rgb lerpRgb(Rgb start, Rgb end, float x) {
    return {
        lerpU8(start.red, end.red, x),
        lerpU8(start.green, end.green, x),
        lerpU8(start.blue, end.blue, x),
    };
}

class Gradient {
   public:
    [[nodiscard]] static Rgb get(float x) {
        const float index = x / (colors.size() - 1);
        const Rgb low = colors[trunc(index)];
        const Rgb high = colors[trunc(index) + 1];
        return lerpRgb(low, high, index - trunc(index));
    }

   private:
    static constexpr std::array<Rgb, 9> colors{
        catpuccin::Red,    catpuccin::Maroon,   catpuccin::Peach,
        catpuccin::Yellow, catpuccin::Green,    catpuccin::Teal,
        catpuccin::Sky,    catpuccin::Sapphire, catpuccin::Blue,
    };
};
