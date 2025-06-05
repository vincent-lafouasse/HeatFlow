#pragma once

#include <array>
#include <cmath>

#include "Rgb.hpp"

class ColorMap {
   public:
    static Rgb get(float x);

   private:
    static constexpr std::array<Rgb, 9> colors{
        catpuccin::Red,    catpuccin::Maroon,   catpuccin::Peach,
        catpuccin::Yellow, catpuccin::Green,    catpuccin::Teal,
        catpuccin::Sky,    catpuccin::Sapphire, catpuccin::Blue,
    };
};
