#include "rasterize.hpp"

#include "screen.hpp"

// Barycentric formula
void rasterize(std::tuple<glm::vec3, glm::vec3, glm::vec3> triangle,
               uint32_t color) {

  auto a = screen(std::get<0>(triangle));
  auto b = screen(std::get<1>(triangle));
  auto c = screen(std::get<2>(triangle));

  glm::vec2 u = {b.x - a.x, b.y - a.y};
  glm::vec2 v = {c.x - a.x, c.y - a.y};

  float det = u.x * v.y - u.y * v.x;
  if (det >= 0.0f)
    return;

  // bounding boxes so we aren't looping over all pixels
  int min_x = std::max(0, int(std::min({a.x, b.x, c.x})));
  int max_x = std::min(int(width) - 1, int(std::max({a.x, b.x, c.x})));

  int min_y = std::max(0, int(std::min({a.y, b.y, c.y})));
  int max_y = std::min(int(height) - 1, int(std::max({a.y, b.y, c.y})));

  for (int y = min_y; y <= max_y; y++) {
    for (int x = min_x; x <= max_x; x++) {
      glm::vec3 q = {x - a.x, y - a.y};

      // t and s tell us how far along each vector we are
      float t = (u.x * q.y - u.y * q.x) / det;
      float s = (q.x * v.y - q.y * v.x) / det;

      if (s + t <= 1 && s >= 0 && t >= 0) {
        float z = (1.0f - s - t) * a.z + s * b.z + t * c.z;

        if (z < zbuffer[y * width + x]) {
          zbuffer[y * width + x] = z;
          buffer[y * width + x] = color;
        }
      }
    }
  }
}
