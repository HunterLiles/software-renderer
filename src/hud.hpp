#pragma once

#include <string_view>

#include "color.hpp"
#include "hunter_math.hpp"
#include "screen.hpp"

constexpr std::string_view characters =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ:.-";

constexpr uint8_t font[][7] = {
    {14, 17, 19, 21, 25, 17, 14}, // 0
    {4, 12, 4, 4, 4, 4, 14},      // 1
    {14, 17, 1, 2, 4, 8, 31},     // 2
    {30, 1, 1, 14, 1, 1, 30},     // 3
    {2, 6, 10, 18, 31, 2, 2},     // 4
    {31, 16, 16, 30, 1, 1, 30},   // 5
    {14, 16, 16, 30, 17, 17, 14}, // 6
    {31, 1, 2, 4, 8, 8, 8},       // 7
    {14, 17, 17, 14, 17, 17, 14}, // 8
    {14, 17, 17, 15, 1, 1, 14},   // 9
    {14, 17, 17, 31, 17, 17, 17}, // A
    {30, 17, 17, 30, 17, 17, 30}, // B
    {14, 17, 16, 16, 16, 17, 14}, // C
    {30, 17, 17, 17, 17, 17, 30}, // D
    {31, 16, 16, 30, 16, 16, 31}, // E
    {31, 16, 16, 30, 16, 16, 16}, // F
    {14, 17, 16, 23, 17, 17, 15}, // G
    {17, 17, 17, 31, 17, 17, 17}, // H
    {14, 4, 4, 4, 4, 4, 14},      // I
    {7, 2, 2, 2, 18, 18, 12},     // J
    {17, 18, 20, 24, 20, 18, 17}, // K
    {16, 16, 16, 16, 16, 16, 31}, // L
    {17, 27, 21, 21, 17, 17, 17}, // M
    {17, 25, 21, 19, 17, 17, 17}, // N
    {14, 17, 17, 17, 17, 17, 14}, // O
    {30, 17, 17, 30, 16, 16, 16}, // P
    {14, 17, 17, 17, 21, 18, 13}, // Q
    {30, 17, 17, 30, 20, 18, 17}, // R
    {15, 16, 16, 14, 1, 1, 30},   // S
    {31, 4, 4, 4, 4, 4, 4},       // T
    {17, 17, 17, 17, 17, 17, 14}, // U
    {17, 17, 17, 17, 17, 10, 4},  // V
    {17, 17, 17, 21, 21, 21, 10}, // W
    {17, 17, 10, 4, 10, 17, 17},  // X
    {17, 17, 10, 4, 4, 4, 4},     // Y
    {31, 1, 2, 4, 8, 16, 31},     // Z
    {0, 4, 4, 0, 4, 4, 0},        // :
    {0, 0, 0, 0, 0, 0, 4},        // .
    {0, 0, 0, 31, 0, 0, 0}        // -
};

static_assert(sizeof(font) / sizeof(font[0]) == characters.size());

void draw_text(int x, int y, std::string_view text, uint32_t color,
               int scale = 1) {
  if (scale <= 0)
    return;

  const int start_x = x;

  for (char ch : text) {
    if (ch == '\n') {
      x = start_x;
      y += 8 * scale;
      continue;
    }

    auto index = characters.find(ch);

    if (index != std::string_view::npos) {
      for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
          if (!(font[index][row] & (1u << (4 - col))))
            continue;

          for (int dy = 0; dy < scale; dy++) {
            for (int dx = 0; dx < scale; dx++) {
              int px = x + col * scale + dx;
              int py = y + row * scale + dy;

              if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
                buffer[py * WIDTH + px] = color;
            }
          }
        }
      }
    }

    x += 6 * scale;
  }
}

void hud(std::string_view text, float opacity = 0.6f) {
  float visibility = 1.0f - std::clamp(opacity, 0.0f, 1.0f);

  // define the box to draw the hud
  int min_x = 10;
  int max_x = 210;

  int min_y = 10;
  int max_y = 210;

  // make a dark box that is see through
  for (int x = min_x; x <= max_x; x++) {
    for (int y = min_y; y <= max_y; y++) {
      uint32_t &pixel = buffer[y * WIDTH + x];

      Color darkened = {uint8_t(((pixel >> 16) & 0xffu) * visibility),
                        uint8_t(((pixel >> 8) & 0xffu) * visibility),
                        uint8_t((pixel & 0xffu) * visibility)};

      pixel = pack_color(darkened);
    }
  }

  draw_text(min_x + 8, min_y + 8, "STATS", pack_color(WHITE), 2);
  draw_text(min_x + 8, min_y + 28, text, pack_color(WHITE), 2);
}
