#pragma once

#include <fstream>
#include <glm/vec3.hpp>
#include <iostream>
#include <sstream>
#include <string_view>

struct LoadObj {
  std::vector<glm::vec3> vertices;
  std::vector<std::tuple<int, int, int>> faces;

  void load_obj_file(std::string_view name) {
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
        glm::vec3 v;
        stream >> v.x >> v.y >> v.z;
        vertices.push_back(v);
      } else if (type == "f") {
        std::string x, y, z;
        stream >> x >> y >> z;

        // faces is a collection of indecies for vertices so it needs to
        // subtract one for accurate indexing.
        std::tuple<int, int, int> f = {std::stoi(x) - 1, std::stoi(y) - 1,
                                       std::stoi(z) - 1};
        faces.push_back(f);
      }
    }
    file.close();
  }
};
