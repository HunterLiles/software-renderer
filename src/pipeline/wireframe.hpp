#pragma once

#include <glm/vec3.hpp>

class Wireframe {
private:
public:
  void line(glm::vec3 start, glm::vec3 end);
  void wireframe(glm::vec3 a, glm::vec3 b, glm::vec3 c);
};
