#pragma once

#include <vector>

#include "Rgb.hpp"

class ColorMap {
   public:
    Rgb get(float x) const;
    static ColorMap Catpuccin();
    static ColorMap Viridis();

   private:
    ColorMap(const std::vector<Rgb>& c);

    std::vector<Rgb> colors;
};
