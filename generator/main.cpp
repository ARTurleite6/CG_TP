#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "input/input.h"
#include <array>
#include <cstddef>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <stdexcept>
#include <iomanip>

void writeVec(std::ofstream &file, const glm::vec3 &vec) {
  file << std::setprecision(10) << vec.x << ' ' << vec.y << ' ' << vec.z << '\n';
}

struct Rectangle {
  std::array<glm::vec3, 6> vertices;
  float size;

  Rectangle(std::array<glm::vec3, 6> vertices, float size)
      : vertices(vertices), size(size) {
    glm::mat4 mat(1.0f);
    mat = glm::translate(mat, {-size / 2.0f, 0.0f, size / 2.0f});

    for (int i = 0; i < 6; ++i) {
        std::cout << "before: \n";
        std::cout << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << '\n';
      vertices[i] = mat * glm::vec4(vertices[i], 1.0f);
        std::cout << "after: \n";
        std::cout << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << '\n';
    }
  }

  Rectangle translate(const glm::vec3 &vec) {
    glm::mat4 mat(1.0f);
    auto trans = glm::translate(mat, vec);
    std::array<glm::vec3, 6> newVertices{};
    for (int i = 0; i < 6; ++i) {
      newVertices[i] = trans * glm::vec4(vertices[i], 1.0f);
    }
    return {newVertices, size};
  }
};

struct Plane {
  std::vector<Rectangle> rectangles;
};

int main(int argc, char *argv[]) {

  using namespace input;
  try {
    Input input(argc, argv);
    std::cout << input << '\n';

    glm::vec3 v1(0.0f, 0.0f, 0.0f);
    glm::vec3 v2(1.0f, 0.0f, 0.0f);
    glm::vec3 v3(0.0f, 0.0f, -1.0f);
    glm::vec3 v4(1.0f, 0.0f, 0.0f);
    glm::vec3 v5(1.0f, 0.0f, -1.0f);
    glm::vec3 v6(0.0f, 0.0f, -1.0f);

    Rectangle rec{{v1, v2, v3, v4, v5, v6}, 1.0f};

    std::vector<Rectangle> rectangles{};
    const auto N = input.getDimensions()[1];
    rectangles.reserve(N * N);

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        auto rec2 = rec.translate({i, 0.0f, -j});
        rectangles.push_back(rec2);
      }
    }

    std::ofstream file;
    file.open(input.getOutFile());

    if (!file.is_open()) {
      std::cout << "Error opening file" << std::endl;
      return 1;
    }

    for (const auto &rec : rectangles) {
      for (auto &vec : rec.vertices) {
          std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << '\n';
        writeVec(file, vec);
      }
    }

  } catch (const std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
