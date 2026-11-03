#pragma once

#include "color.hpp"
#include "hunter_math.hpp"
#include "screen.hpp"

void line(vec3<float> start, vec3<float> end) {

  bool steep = std::abs(start.x - end.x) < std::abs(start.y - end.y);
  if (steep) {
    start = {start.y, start.x};
    end = {end.y, end.x};
  }

  if (start.x > end.x) {
    std::swap(start.x, end.x);
    std::swap(start.y, end.y);
  }

  for (int x = std::round(start.x); x <= std::round(end.x); x++) {
    int y = std::round(start.y +
                       (x - start.x) * ((end.y - start.y) / (end.x - start.x)));

    if (steep)
      buffer[x * WIDTH + y] = pack_color(GREEN);
    else
      buffer[y * WIDTH + x] = pack_color(GREEN);
  }
}

void triangle(vec3<float> a, vec3<float> b, vec3<float> c) {
  line(a, b);
  line(b, c);
  line(c, a);
}
