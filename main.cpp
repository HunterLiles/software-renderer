#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>

#include "MiniFB/include/MiniFB.h"

// packing colors to fit inside uint32_t buffer
constexpr uint32_t pack_color(uint8_t r, uint8_t g, uint8_t b,
                              uint8_t a = 255) {
  return (a << 24) | (r << 16) | (g << 8) | b;
}
// RGBA ordering
constexpr uint32_t WHITE = pack_color(255, 255, 255);
constexpr uint32_t GREEN = pack_color(0, 255, 0);
constexpr uint32_t RED = pack_color(255, 0, 0);
constexpr uint32_t BLUE = pack_color(64, 128, 255);
constexpr uint32_t YELLOW = pack_color(255, 200, 0);

// Screen
constexpr uint16_t WIDTH = 1280;
constexpr uint16_t HEIGHT = 720;
constexpr float RATIO = float(WIDTH) / float(HEIGHT);

uint32_t *buffer = new uint32_t[WIDTH * HEIGHT]{};

template <typename T> struct vec2 {
  T x, y;
};

template <typename T> struct vec3 {
  T x, y, z;
};

void load_obj_file(std::string_view name, std::vector<vec3<float>> &vertices,
                   std::vector<vec3<int>> &faces) {
  // load in file
  std::ifstream file(name.data());
  if (!file.is_open())
    std::cerr << "Error opening the file!";

  // Make variable to hold each vertice and face in
  std::string s;

  // store vertices and faces from file
  while (std::getline(file, s)) {
    std::istringstream stream(s);
    std::string type;

    stream >> type;

    if (type == "v") {
      vec3<float> v;
      stream >> v.x >> v.y >> v.z;
      vertices.push_back(v);
    } else if (type == "f") {
      std::string x, y, z;
      stream >> x >> y >> z;

      // faces is a collection of indecies for vertices so it needs to subtract
      // one for accurate indexing.
      vec3<int> f = {std::stoi(x) - 1, std::stoi(y) - 1, std::stoi(z) - 1};
      faces.push_back(f);
    }
  }
  file.close();
}

// turn 3d coordinates into 2d coordinates
vec2<float> projection(vec3<float> p) {
  p.z += 2.0f;

  // Projecting p into 2d space
  float x = p.x / (p.z * RATIO); // keep aspect correct
  float y = p.y / p.z;
  return {x, -y};
}

// translate from object coordinates to screen coordinates
vec2<float> translate(vec2<float> p) {
  float x = (p.x + 1.0f) * WIDTH / 2.0f;
  float y = (p.y + 1.0f) * HEIGHT / 2.0f;

  return {x, y};
}

void line(vec2<float> start, vec2<float> end) {

  bool steep = std::abs(start.x - end.x) < std::abs(start.y - end.y);
  if (steep) {
    start = {start.y, start.x};
    end = {end.y, end.x};
  }

  if (start.x > end.x) {
    std::swap(start.x, end.x);
    std::swap(start.y, end.y);
  }

  for (int x = std::round(start.x); x <= std::round(end.x); x++) {
    int y = std::round(start.y +
                       (x - start.x) * ((end.y - start.y) / (end.x - start.x)));

    if (steep)
      buffer[x * WIDTH + y] = GREEN;
    else
      buffer[y * WIDTH + x] = GREEN;
  }
}

void triangle(vec2<float> &a, vec2<float> &b, vec2<float> &c) {
  line(a, b);
  line(b, c);
  line(c, a);
}

int main(int argc, char **argv) {

  struct mfb_window *window =
      mfb_open_ex("Software Renderer", WIDTH, HEIGHT, MFB_WF_RESIZABLE);
  if (window == nullptr)
    return 0;

  mfb_update_state state;
  do {

    std::vector<vec3<float>> vertices;
    std::vector<vec3<int>> faces;

    std::vector<std::string_view> names{"obj/diablo3_pose/diablo3_pose.obj",
                                        "obj/floor.obj"};

    // for (int i{}; i < int(names.size()); i++) {
    //   load_obj_file(names[i], vertices, faces);
    // }

    load_obj_file(names[0], vertices, faces);

    // loop over faces to see needed vertices
    // use the found vertices to draw a wireframe
    for (int i{}; i < int(faces.size()); i++) {
      vec3<int> face = faces[i];

      auto a = translate(projection(vertices[face.x]));
      auto b = translate(projection(vertices[face.y]));
      auto c = translate(projection(vertices[face.z]));

      triangle(a, b, c);
    }

    // update buffer
    state = mfb_update_ex(window, buffer, WIDTH, HEIGHT);

    if (state != MFB_STATE_OK)
      break;
  } while (mfb_wait_sync(window));

  // Free everything
  delete[] buffer;
  buffer = nullptr;
  window = nullptr;
  return 0;
}
