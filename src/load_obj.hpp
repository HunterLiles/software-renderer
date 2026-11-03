#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

#include "hunter_math.hpp"

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

      // faces is a collection of indecies for vertices so it needs to
      // subtract one for accurate indexing.
      vec3<int> f = {std::stoi(x) - 1, std::stoi(y) - 1, std::stoi(z) - 1};
      faces.push_back(f);
    }
  }
  file.close();
}
