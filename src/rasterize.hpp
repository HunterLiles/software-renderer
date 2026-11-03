#pragma once

#include "hunter_math.hpp"
#include "screen.hpp"

// Barycentric formula
void rasterize(Triangle triangle, vec3<float> move, uint32_t color) {
  auto a = screen(triangle.a, move);
  auto b = screen(triangle.b, move);
  auto c = screen(triangle.c, move);

  vec2<float> u = {b.x - a.x, b.y - a.y};
  vec2<float> v = {c.x - a.x, c.y - a.y};

  float det = u.x * v.y - u.y * v.x;
  if (det <= 0.0f)
    return;

  // bounding boxes so we aren't looping over all pixels
  int min_x = std::max(0, int(std::min({a.x, b.x, c.x})));
  int max_x = std::min(int(width) - 1, int(std::max({a.x, b.x, c.x})));

  int min_y = std::max(0, int(std::min({a.y, b.y, c.y})));
  int max_y = std::min(int(height) - 1, int(std::max({a.y, b.y, c.y})));

  float inv_a = 1.0f / a.z;
  float inv_b = 1.0f / b.z;
  float inv_c = 1.0f / c.z;

  // #pragma omp parallel for
  for (int y = min_y; y <= max_y; y++) {
    for (int x = min_x; x <= max_x; x++) {
      // t and s tell us how far along each vector we are
      vec3<float> q = {x - a.x, y - a.y};

      float t = (u.x * q.y - u.y * q.x) / det;
      float s = (q.x * v.y - q.y * v.x) / det;

      if (s + t <= 1 && s >= 0 && t >= 0) {
        float inv_z = (1.0f - s - t) * inv_a + s * inv_b + t * inv_c;

        if (inv_z > zbuffer[y * width + x]) {
          zbuffer[y * width + x] = inv_z;
          buffer[y * width + x] = color;
        }
      }
    }
  }
}
