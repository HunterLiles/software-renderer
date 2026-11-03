#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

#include "screen.hpp"

template <typename T> struct vec2 {
  T x, y;
};

template <typename T> struct vec3 {
  T x, y, z;

  vec3<T> operator-(float b) { return vec3<T>(x - b, y - b, z - b); }
  vec3<T> operator+(float b) { return vec3<T>(x + b, y + b, z + b); }
  vec3<T> operator*(float b) { return vec3<T>(x * b, y * b, z * b); }
  vec3<T> operator/(float b) { return vec3<T>(x / b, y / b, z / b); }
};

template <typename T> struct vec4 {
  T x, y, z, w;
};

struct Triangle {
  vec3<float> a, b, c;
};

// turn 3d coordinates into 2d coordinates
vec3<float> screen(vec3<float> p, vec3<float> move) {
  p.x = -p.x;
  p.z = -p.z;

  p.x += move.x;
  p.y += move.y;
  p.z += move.z;

  // Projecting p into 2d space
  float x = p.x / (p.z * RATIO); // keep aspect correct
  float y = -p.y / p.z;

  return {(x + 1.0f) * WIDTH / 2.0f, (y + 1.0f) * HEIGHT / 2.0f, p.z};
}
