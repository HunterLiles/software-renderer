#include <chrono>

#include "MiniFB.h"
#include "color.hpp"
#include "hud.hpp"
#include "hunter_math.hpp"
#include "lighting.hpp"
#include "load_obj.hpp"
#include "rasterize.hpp"
#include "screen.hpp"

int main(int argc, char **argv) {

  struct mfb_window *window =
      mfb_open_ex("Software Renderer", width, height, MFB_WF_RESIZABLE);
  if (window == nullptr)
    return 0;

  mfb_update_state state;

  std::vector<vec3<float>> vertices;
  std::vector<vec3<int>> faces;

  std::vector<std::string_view> names{"obj/diablo3_pose/diablo3_pose.obj",
                                      "obj/floor.obj"};

  // for (int i{}; i < int(names.size()); i++) {
  //   load_obj_file(names[i], vertices, faces);
  // }

  load_obj_file(names[0], vertices, faces);

  using Clock = std::chrono::steady_clock;

  auto previous = Clock::now();
  double total_time = 0.0;
  double elapsed = 0.0;
  unsigned frames = 0;

  char stats[64] = "FPS: --\nFRAME: -- MS";

  vec3<float> move = {0.0f, 0.0f, 1.25f};
  do {
    auto new_width = mfb_get_window_width(window);
    auto new_height = mfb_get_window_height(window);

    if (new_width == 0 || new_height == 0)
      continue;

    if (new_width != width || new_height != height) {
      delete[] buffer;
      delete[] zbuffer;

      width = new_width;
      height = new_height;
      ratio = float(width) / float(height);

      buffer = new uint32_t[width * height];
      zbuffer = new float[width * height];
    }

    std::fill(buffer, buffer + width * height, 0u);
    std::fill(zbuffer, zbuffer + width * height, 0u);

    auto now = Clock::now();
    float dt = std::chrono::duration<float>(now - previous).count();
    previous = now;

    total_time += dt;
    elapsed += dt;

    for (int i{}; i < int(faces.size()); i++) {
      vec3<int> face = faces[i];

      auto a = vertices[face.x];
      auto b = vertices[face.y];
      auto c = vertices[face.z];

      float brightness = lighting({a, b, c}, total_time);
      uint32_t color = pack_color(WHITE * brightness);

      rasterize({a, b, c}, move, color);
    }

    hud(stats, 0.6f);

    // update buffer
    state = mfb_update_ex(window, buffer, width, height);
    if (state != MFB_STATE_OK)
      break;

    // FPS and Frametime
    previous = now;
    frames++;

    if (elapsed >= 0.25) {
      double fps = frames / elapsed;
      double frame_ms = 1000.0 * elapsed / frames;

      std::snprintf(stats, sizeof(stats), "FPS: %.1f\nFRAMETIME: %.4f MS", fps,
                    frame_ms);

      elapsed = 0.0;
      frames = 0;
    }
  } while (mfb_wait_sync(window));

  // Free everything
  delete[] buffer;
  delete[] zbuffer;
  window = nullptr;
  return 0;
}
