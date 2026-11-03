#include "wireframe.hpp"

#include "color.hpp"
#include "screen.hpp"
#include <cmath>

void line(glm::vec3 start, glm::vec3 end) {

  bool steep = std::abs(start.x - end.x) < std::abs(start.y - end.y);
  if (steep) {
    std::swap(start.y, start.x);
    std::swap(end.y, end.x);
  }

  if (start.x > end.x) {
    std::swap(start.x, end.x);
    std::swap(start.y, end.y);
  }

  for (int x = std::round(start.x); x <= std::round(end.x); x++) {
    int y = std::round(start.y +
                       (x - start.x) * ((end.y - start.y) / (end.x - start.x)));

    if (steep)
      buffer[x * width + y] = pack_color(GREEN);
    else
      buffer[y * width + x] = pack_color(GREEN);
  }
}

void wireframe(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
  line(a, b);
  line(b, c);
  line(c, a);
}
