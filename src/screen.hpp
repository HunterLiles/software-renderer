#pragma once

#include "MiniFB.h"
#include <cstdint>

// Screen
uint32_t width = 1280;
uint32_t height = 720;
float aspect = float(width) / float(height);

uint32_t *buffer = new uint32_t[width * height]{};
float *zbuffer = new float[width * height]{};

void update_window(mfb_window *window) {
  auto new_width = mfb_get_window_width(window);
  auto new_height = mfb_get_window_height(window);

  if (new_width == 0 || new_height == 0)
    return;

  if (new_width != width || new_height != height) {
    delete[] buffer;
    delete[] zbuffer;

    width = new_width;
    height = new_height;
    aspect = float(width) / float(height);

    buffer = new uint32_t[width * height];
    zbuffer = new float[width * height];
  }
}

void cleanup(mfb_window *window) {
  delete[] buffer;
  delete[] zbuffer;
  window = nullptr;
}
