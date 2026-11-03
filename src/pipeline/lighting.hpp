#pragma once

#include <glm/glm.hpp>

class Lighting {
private:
public:
  float lighting(std::tuple<glm::vec3, glm::vec3, glm::vec3> t, float time) {
    glm::vec3 light = {2 * std::cos(time), 2 * std::sin(time), std::cos(time)};
    glm::vec3 light_norm = glm::normalize(light);

    glm::vec3 u = {std::get<1>(t).x - std::get<0>(t).x,
                   std::get<1>(t).y - std::get<0>(t).y,
                   std::get<1>(t).z - std::get<0>(t).z};
    glm::vec3 v = {std::get<2>(t).x - std::get<0>(t).x,
                   std::get<2>(t).y - std::get<0>(t).y,
                   std::get<2>(t).z - std::get<0>(t).z};

    glm::vec3 cross = glm::cross(u, v);
    glm::vec3 normal = glm::normalize(cross);

    float dot = glm::dot(normal, light_norm);

    float ambient = 0.15f;
    return std::max(ambient, dot);
  }
};
