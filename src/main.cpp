#include "color.hpp"
#include "hud.hpp"
#include "lighting.hpp"
#include "load_obj.hpp"
#include "rasterize.hpp"
#include "screen.hpp"

#include <glm/vec3.hpp>
#include <limits>

int main(int argc, char **argv) {
  Window screen{.width = 800, .height = 600};

  struct mfb_window *window = mfb_open_ex("Software Renderer", screen.width,
                                          screen.height, MFB_WF_RESIZABLE);
  if (window == nullptr)
    return 0;

  mfb_update_state state;

  std::vector<std::string_view> names{"obj/diablo3_pose/diablo3_pose.obj",
                                      "obj/floor.obj"};

  LoadObj load;
  load.load_obj_file(names[0]);

  HUD hud;
  hud.init_time();

  do {
    // update buffer width and height to window
    screen.update_window(window);
    hud.update_time();

    std::fill(screen.buffer, screen.buffer + screen.width * screen.height, 0u);
    std::fill(screen.zbuffer, screen.zbuffer + screen.width * screen.height,
              std::numeric_limits<float>::infinity());

    for (int i{}; i < int(load.faces.size()); i++) {
      std::tuple<int, int, int> face = load.faces[i];

      auto a = load.vertices[std::get<0>(face)];
      auto b = load.vertices[std::get<1>(face)];
      auto c = load.vertices[std::get<2>(face)];

      float brightness = Lighting::lighting({a, b, c}, hud.stats.total_time);
      Color color{WHITE * brightness};

      Rasterize::rasterize({a, b, c}, color.pack_color());
    }

    hud.hud();
    hud.FPS();

    // update buffer
    state = mfb_update_ex(window, screen.buffer, screen.width, screen.height);
    if (state != MFB_STATE_OK)
      break;
  } while (mfb_wait_sync(window));

  // Free everything
  screen.cleanup(window);
  return 0;
}
