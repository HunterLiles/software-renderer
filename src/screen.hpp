#pragma once

#include <cstdint>

// Screen
constexpr uint16_t WIDTH = 1280;
constexpr uint16_t HEIGHT = 720;
constexpr float RATIO = float(WIDTH) / float(HEIGHT);

uint32_t *buffer = new uint32_t[WIDTH * HEIGHT]{};
float *zbuffer = new float[WIDTH * HEIGHT]{};
