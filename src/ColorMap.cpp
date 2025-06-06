#include "ColorMap.hpp"

#include <cmath>

static u8 u8FromFloat(float x) {
    if (x > 255.0f) {
        return 255;
    } else if (x < 0.0f) {
        return 0;
    } else {
        return static_cast<u8>(std::floor(x));
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

Rgb ColorMap::get(float x) const {
    if (x <= 0.0f) {
        return colors.front();
    }
    if (x >= 1.0f) {
        return colors.back();
    }

    const float floatIndex = x * (colors.size() - 1);
    const usize index = static_cast<usize>(std::floor(floatIndex));
    const float offset = floatIndex - index;

    const Rgb low = colors[index];
    const Rgb high = colors[index + 1];
    return lerpRgb(low, high, offset);
}

ColorMap::ColorMap(const std::vector<Rgb>& c) : colors(c) {}

ColorMap ColorMap::Catpuccin() {
    std::vector<Rgb> colors = {
        catpuccin::Blue,   /*catpuccin::Sapphire,*/ catpuccin::Sky,
        catpuccin::Teal,   catpuccin::Green,
        catpuccin::Yellow, catpuccin::Peach,
        catpuccin::Maroon, catpuccin::Red,
    };

    return ColorMap(colors);
}

ColorMap ColorMap::Viridis() {
    std::vector<Rgb> colors = {
        Rgb::fromHex(0xfde725), Rgb::fromHex(0xf1e51d), Rgb::fromHex(0xe5e419),
        Rgb::fromHex(0xd8e219), Rgb::fromHex(0xcae11f), Rgb::fromHex(0xbade28),
        Rgb::fromHex(0xaddc30), Rgb::fromHex(0xa0da39), Rgb::fromHex(0x93d741),
        Rgb::fromHex(0x84d44b), Rgb::fromHex(0x77d153), Rgb::fromHex(0x6ccd5a),
        Rgb::fromHex(0x60ca60), Rgb::fromHex(0x56c667), Rgb::fromHex(0x4ac16d),
        Rgb::fromHex(0x40bd72), Rgb::fromHex(0x38b977), Rgb::fromHex(0x31b57b),
        Rgb::fromHex(0x29af7f), Rgb::fromHex(0x25ab82), Rgb::fromHex(0x21a685),
        Rgb::fromHex(0x1fa187), Rgb::fromHex(0x1e9d89), Rgb::fromHex(0x1f978b),
        Rgb::fromHex(0x20928c), Rgb::fromHex(0x218e8d), Rgb::fromHex(0x23898e),
        Rgb::fromHex(0x25838e), Rgb::fromHex(0x277f8e), Rgb::fromHex(0x297a8e),
        Rgb::fromHex(0x2b758e), Rgb::fromHex(0x2d718e), Rgb::fromHex(0x2f6b8e),
        Rgb::fromHex(0x31668e), Rgb::fromHex(0x34618d), Rgb::fromHex(0x365c8d),
        Rgb::fromHex(0x39558c), Rgb::fromHex(0x3c508b), Rgb::fromHex(0x3e4a89),
        Rgb::fromHex(0x404588), Rgb::fromHex(0x423f85), Rgb::fromHex(0x453882),
        Rgb::fromHex(0x46327e), Rgb::fromHex(0x472c7a), Rgb::fromHex(0x482576),
        Rgb::fromHex(0x481d6f), Rgb::fromHex(0x481769), Rgb::fromHex(0x471063),
        Rgb::fromHex(0x46085c), Rgb::fromHex(0x440154),
    };

    return ColorMap(colors);
}

ColorMap ColorMap::Inferno() {
    std::vector<Rgb> colors = {
        Rgb::fromHex(0xfcffa4), Rgb::fromHex(0xf5f992), Rgb::fromHex(0xf2f27d),
        Rgb::fromHex(0xf2ea69), Rgb::fromHex(0xf4e156), Rgb::fromHex(0xf6d543),
        Rgb::fromHex(0xf9cb35), Rgb::fromHex(0xfac228), Rgb::fromHex(0xfbb81d),
        Rgb::fromHex(0xfcac11), Rgb::fromHex(0xfca309), Rgb::fromHex(0xfb9906),
        Rgb::fromHex(0xfa9008), Rgb::fromHex(0xf8870e), Rgb::fromHex(0xf57d15),
        Rgb::fromHex(0xf2741c), Rgb::fromHex(0xef6c23), Rgb::fromHex(0xeb6429),
        Rgb::fromHex(0xe55c30), Rgb::fromHex(0xe05536), Rgb::fromHex(0xda4e3c),
        Rgb::fromHex(0xd44842), Rgb::fromHex(0xce4347), Rgb::fromHex(0xc63d4d),
        Rgb::fromHex(0xbf3952), Rgb::fromHex(0xb73557), Rgb::fromHex(0xb0315b),
        Rgb::fromHex(0xa62d60), Rgb::fromHex(0x9f2a63), Rgb::fromHex(0x972766),
        Rgb::fromHex(0x8f2469), Rgb::fromHex(0x87216b), Rgb::fromHex(0x7d1e6d),
        Rgb::fromHex(0x751b6e), Rgb::fromHex(0x6d186e), Rgb::fromHex(0x65156e),
        Rgb::fromHex(0x5c126e), Rgb::fromHex(0x540f6d), Rgb::fromHex(0x4c0c6b),
        Rgb::fromHex(0x440a68), Rgb::fromHex(0x3b0964), Rgb::fromHex(0x310a5c),
        Rgb::fromHex(0x280b53), Rgb::fromHex(0x1f0c48), Rgb::fromHex(0x180c3c),
        Rgb::fromHex(0x10092d), Rgb::fromHex(0x0a0722), Rgb::fromHex(0x050417),
        Rgb::fromHex(0x02020c), Rgb::fromHex(0x000004),
    };

    return ColorMap(colors);
}
