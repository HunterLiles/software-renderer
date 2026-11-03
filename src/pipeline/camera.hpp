#pragma once

#include <glm/glm.hpp>

class Camera {
private:
  glm::vec3 pos{};
  glm::vec3 up{0.0f, 1.0f, 0.0f}, right{1.0f, 0.0f, 0.0f},
      forward{0.0f, 0.0f, 1.0f};

  glm::vec3 F, R, U;

  void setViewport() {}
  void setPerspective() {}
  void lookAt() {}

public:
  void camera() {
    setViewport();
    setPerspective();
    lookAt();
  }
};
