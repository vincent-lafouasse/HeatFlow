#pragma once

struct Mass {
    float grams;

    [[nodiscard]] static constexpr Mass from_kilos(float k) {
        return {1000.0f * k};
    }
    [[nodiscard]] static constexpr Mass from_grams(float g) { return {g}; }

    [[nodiscard]] constexpr float as_kilos() const { return grams / 1000.0f; }
    [[nodiscard]] constexpr float as_grams() const { return grams; }
    [[nodiscard]] constexpr float si() const { return as_kilos(); }
};

struct Length {
    float millis;

    [[nodiscard]] static constexpr Length from_meters(float m) {
        return {1000.0f * m};
    }
    [[nodiscard]] static constexpr Length from_millis(float m) { return {m}; }

    [[nodiscard]] constexpr float as_meters() const { return millis / 1000.0f; }
    [[nodiscard]] constexpr float as_millis() const { return millis; }
    [[nodiscard]] constexpr float si() const { return as_meters(); }
};

struct Duration {
    float millis;

    [[nodiscard]] static constexpr Duration from_secs(float s) {
        return {1000.0f * s};
    }
    [[nodiscard]] static constexpr Duration from_millis(float m) { return {m}; }

    [[nodiscard]] constexpr float as_secs() const { return millis / 1000.0f; }
    [[nodiscard]] constexpr float as_millis() const { return millis; }
    [[nodiscard]] constexpr float si() const { return as_secs(); }
};
