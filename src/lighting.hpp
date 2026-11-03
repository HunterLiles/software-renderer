#pragma once

#include "hunter_math.hpp"

float lighting(Triangle t, float time) {
  vec3<float> light = {2 * std::cos(time), 2 * std::sin(time), std::cos(time)};
  float light_len =
      std::sqrt(light.x * light.x + light.y * light.y + light.z * light.z);
  vec3<float> light_norm = {light.x / light_len, light.y / light_len,
                            light.z / light_len};

  vec3<float> u = {t.b.x - t.a.x, t.b.y - t.a.y, t.b.z - t.a.z};
  vec3<float> v = {t.c.x - t.a.x, t.c.y - t.a.y, t.c.z - t.a.z};

  vec3<float> cross = {(u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z),
                       (u.x * v.y) - (u.y * v.x)};
  float magnitude =
      std::sqrt(cross.x * cross.x + cross.y * cross.y + cross.z * cross.z);

  vec3<float> normal = {cross.x / magnitude, cross.y / magnitude,
                        cross.z / magnitude};

  float dot = normal.x * light_norm.x + normal.y * light_norm.y +
              normal.z * light_norm.z;

  constexpr float ambient = 0.15f;
  float diffuse = std::max(ambient, dot);

  return diffuse;
}
