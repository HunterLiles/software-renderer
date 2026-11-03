#pragma once

#include <algorithm>

#include <cstdint>
#include <numbers>
#include <vector>

#include "matrix.hpp"
#include "screen.hpp"
#include "vector.hpp"

struct Triangle {
  vec3<float> a, b, c;
};

struct Camera {
  mat<4, 4> ModelView, Viewport, Perspective;
  vec3<float> eye, center, up;
} camera;

void setViewport() {
  camera.Viewport = {{{width / 2.0f, 0, 0, width / 2.0f},
                      {0.0f, -height / 2.0f, 0.0f, height / 2.0f},
                      {0.0f, 0.0f, 1.0f, 0.0f},
                      {0.0f, 0.0f, 0.0f, 1.0f}}};
}

void setPerspective() {
  float fov = 90.0f * std::numbers::pi_v<float> / 180.0f;
  float f = 1.0f / std::tan(fov / 2.0f);

  float near = 0.1f;
  float far = 1000.0f;

  camera.Perspective = {{{f / aspect, 0.0f, 0.0f, 0.0f},
                         {0.0f, f, 0.0f, 0.0f},
                         {0.0f, 0.0f, -(far + near) / (far - near),
                          -(2 * far * near) / (far - near)},
                         {0.0f, 0.0f, -1.0f, 0.0f}}};
}

void lookAt(float x, float y) {
  vec3<float> n = normalize(camera.eye - camera.center);
  vec3<float> l = normalize(cross(camera.up, n));
  vec3<float> m = normalize(cross(n, l));

  camera.ModelView = {{{l.x, l.y, l.z, -dot(l, camera.eye)},
                       {m.x, m.y, m.z, -dot(m, camera.eye)},
                       {n.x, n.y, n.z, -dot(n, camera.eye)},
                       {0, 0, 0, 1}}};
}

// turn 3d coordinates into 2d coordinates
vec3<float> screen(vec3<float> p, vec3<float> move) {
  vec4<float> v = {p.x, p.y, p.z, 1.0f};

  v = camera.Perspective * camera.ModelView * v;

  v.x /= v.w;
  v.y /= v.w;
  v.z /= v.w;
  v.w = 1.0f;

  v = camera.Viewport * v;

  return {v.x, v.y, v.z};
}
