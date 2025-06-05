#pragma once

#include <raylib.h>

#include "ints.hpp"

struct Rgb {
    u8 red;
    u8 green;
    u8 blue;

    [[nodiscard]] static constexpr Rgb fromHex(u32 hex) {
        u8 b = hex & 0xff;
        hex >>= 8;
        u8 g = hex & 0xff;
        hex >>= 8;
        u8 r = hex & 0xff;

        return {r, g, b};
    }

    [[nodiscard]] constexpr Color withAlpha(u8 alpha) const {
        return {red, green, blue, alpha};
    }

    [[nodiscard]] constexpr Color opaque() const {
        return this->withAlpha(0xff);
    }
};

namespace catpuccin {
[[maybe_unused]] static constexpr Rgb darkGray{24, 24, 37};
[[maybe_unused]] static constexpr Rgb lavender{180, 190, 254};
[[maybe_unused]] static constexpr Rgb blue{137, 180, 250};
[[maybe_unused]] static constexpr Rgb teal{148, 226, 213};
[[maybe_unused]] static constexpr Rgb peach{250, 179, 135};
[[maybe_unused]] static constexpr Rgb red{243, 139, 168};
[[maybe_unused]] static constexpr Rgb pink{245, 194, 231};
}  // namespace catpuccin
