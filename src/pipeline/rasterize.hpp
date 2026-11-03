#pragma once

#include <glm/glm.hpp>
#include <tuple>

class Rasterize {
private:
public:
  static void rasterize(std::tuple<glm::vec3, glm::vec3, glm::vec3> triangle,
                        uint32_t color);
};
