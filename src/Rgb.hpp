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
[[maybe_unused]] static constexpr Rgb DarkGray{24, 24, 37};

[[maybe_unused]] static constexpr Rgb Rosewater = Rgb::fromHex(0xf5e0dc);
[[maybe_unused]] static constexpr Rgb Flamingo = Rgb::fromHex(0xf2cdcd);
[[maybe_unused]] static constexpr Rgb Pink = Rgb::fromHex(0xf5c2e7);
[[maybe_unused]] static constexpr Rgb Lavender = Rgb::fromHex(0xb4befe);
[[maybe_unused]] static constexpr Rgb Mauve = Rgb::fromHex(0xcba6f7);

[[maybe_unused]] static constexpr Rgb Red = Rgb::fromHex(0xf38ba8);
[[maybe_unused]] static constexpr Rgb Maroon = Rgb::fromHex(0xeba0ac);
[[maybe_unused]] static constexpr Rgb Peach = Rgb::fromHex(0xfab387);
[[maybe_unused]] static constexpr Rgb Yellow = Rgb::fromHex(0xf9e2af);
[[maybe_unused]] static constexpr Rgb Green = Rgb::fromHex(0xa6e3a1);
[[maybe_unused]] static constexpr Rgb Teal = Rgb::fromHex(0x94e2d5);
[[maybe_unused]] static constexpr Rgb Sky = Rgb::fromHex(0x89dceb);
[[maybe_unused]] static constexpr Rgb Sapphire = Rgb::fromHex(0x74c7ec);
[[maybe_unused]] static constexpr Rgb Blue = Rgb::fromHex(0x89b4fa);
}  // namespace catpuccin
