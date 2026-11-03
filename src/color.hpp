#pragma once

#include <cstdint>

struct Color {
  uint8_t r, g, b;

  Color operator-(float s) const {
    return {uint8_t(r - s), uint8_t(g - s), uint8_t(b - s)};
  }
  Color operator+(float s) const {
    return {uint8_t(r + s), uint8_t(g + s), uint8_t(b + s)};
  }
  Color operator*(float s) const {
    return {uint8_t(r * s), uint8_t(g * s), uint8_t(b * s)};
  }
  Color operator/(float s) const {
    return {uint8_t(r / s), uint8_t(g / s), uint8_t(b / s)};
  }
};

// packing colors to fit inside uint32_t buffer ARGB
constexpr uint32_t pack_color(Color color, uint8_t a = 255) {
  return (a << 24) | (color.r << 16) | (color.g << 8) | color.b;
}

// RGBA ordering
constexpr Color WHITE = {255, 255, 255};
constexpr Color GREEN = {0, 255, 0};
constexpr Color RED = {255, 0, 0};
constexpr Color BLUE = {64, 128, 255};
constexpr Color YELLOW = {255, 200, 0};
