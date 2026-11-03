#pragma once

#include <chrono>
#include <cstdio>

class Time {
private:
  using Clock = std::chrono::steady_clock;

  struct Stats {
    Clock::time_point previous, now;

    float total_time{};
    float elapsed{};
    float dt{};

    int frames{};
    char stats[64]{};
  } stats;

public:
  void init_time() {
    stats.now = Clock::now();
    stats.previous = stats.now;
  }

  void update_time() {
    stats.now = Clock::now();
    stats.dt = std::chrono::duration<float>(stats.now - stats.previous).count();
    stats.previous = stats.now;

    stats.total_time += stats.dt;
    stats.elapsed += stats.dt;
  }

  void FPS() {
    stats.frames++;

    if (stats.elapsed >= 0.25f) {
      float fps = stats.frames / stats.elapsed;
      float frame_ms = 1000.0f * stats.elapsed / stats.frames;

      std::snprintf(stats.stats, sizeof(stats.stats),
                    "FPS: %.1f\nFRAMETIME: %.4f MS", fps, frame_ms);

      stats.elapsed = 0.0f;
      stats.frames = 0;
    }
  }
};
