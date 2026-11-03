#pragma once

#include <cstdint>

// Screen
uint32_t width = 1280;
uint32_t height = 720;
float ratio = float(width) / float(height);

uint32_t *buffer = new uint32_t[width * height]{};
float *zbuffer = new float[width * height]{};
