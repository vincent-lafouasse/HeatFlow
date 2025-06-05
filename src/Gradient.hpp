#pragma once

#include <array>

#include "Rgb.hpp"

class Gradient {
   public:
    [[nodiscard]] static Rgb get(float x) {
        if (x == 1.0f) {
            return colors.back();
        }

        const usize index = static_cast<usize>(x * colors.size());
        return colors[index];
    }

   private:
    static constexpr std::array<Rgb, 9> colors{
        catpuccin::Red,    catpuccin::Maroon,   catpuccin::Peach,
        catpuccin::Yellow, catpuccin::Green,    catpuccin::Teal,
        catpuccin::Sky,    catpuccin::Sapphire, catpuccin::Blue,
    };
};
