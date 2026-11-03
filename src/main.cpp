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

  load_obj_file(names[0], vertices, faces);

  vec3<float> diablo3_move = {0.0f, 0.0f, 1.25f};

  init_time();

  do {
    // update buffer width and height to window
    update_window(window);
    update_time();

    std::fill(buffer, buffer + width * height, 0u);
    std::fill(zbuffer, zbuffer + width * height, 0u);

    for (int i{}; i < int(faces.size()); i++) {
      vec3<int> face = faces[i];

      auto a = vertices[face.x];
      auto b = vertices[face.y];
      auto c = vertices[face.z];

      float brightness = lighting({a, b, c}, stats.total_time);
      uint32_t color = pack_color(WHITE * brightness);

      rasterize({a, b, c}, diablo3_move, color);
    }

    hud(0.6f);

    FPS();

    // update buffer
    state = mfb_update_ex(window, buffer, width, height);
    if (state != MFB_STATE_OK)
      break;
  } while (mfb_wait_sync(window));

  // Free everything
  cleanup(window);
  return 0;
}
