#include "hud.hpp"

#include "color.hpp"
#include "screen.hpp"
#include <algorithm>

void HUD::draw_text(glm::vec2 pos, std::string_view text, uint32_t color,
                    int scale) {
  if (scale <= 0)
    return;

  const int start_x = pos.x;

  for (char ch : text) {
    if (ch == '\n') {
      pos.x = start_x;
      pos.y += 8 * scale;
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
              int px = pos.x + col * scale + dx;
              int py = pos.y + row * scale + dy;

              if (px >= 0 && px < int(width) && py >= 0 && py < int(height))
                buffer[py * width + px] = color;
            }
          }
        }
      }
    }

    pos.x += 6 * scale;
  }
}

void HUD::hud(float opacity) {
  float visibility = 1.0f - std::clamp(opacity, 0.0f, 1.0f);

  // define the box to draw the hud
  glm::vec2 min{10, 10};
  glm::vec2 max{210, 210};

  // make a dark box that is see through
  for (int x = min.x; x <= max.x; x++) {
    for (int y = min.y; y <= max.y; y++) {
      uint32_t &pixel = buffer[y * width + x];

      Color darkened = {uint8_t(((pixel >> 16) & 0xffu) * visibility),
                        uint8_t(((pixel >> 8) & 0xffu) * visibility),
                        uint8_t((pixel & 0xffu) * visibility)};

      pixel = pack_color(darkened);
    }
  }

  draw_text({min.x + 8, min.y + 8}, "STATS", pack_color(WHITE), 2);
  draw_text({min.x + 8, min.y + 28}, stats.stats, pack_color(WHITE), 2);
}
