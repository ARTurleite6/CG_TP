#include "Plane.h"

Plane::Plane(const std::vector<float> &args)
    : Figure(args), dimension(args[0]), divisions(args[1]) {
  std::cout << "computePlane()\n";
  std::cout << "args: " << dimension << ' ' << divisions << '\n';

  float step = dimension / divisions;
  std::cout << "step = " << step << '\n';

  int N = static_cast<int>(divisions);
  std::cout << "N = " << N << '\n';
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {

      Triangle t{{
          Vertex{step * static_cast<float>(i), 0.0f,
                 step * static_cast<float>(j), 1.0f},
          Vertex{step * static_cast<float>(i), 0.0f,
                 step * static_cast<float>(j + 1), 1.0f},
          Vertex{step * static_cast<float>(i + 1), 0.0f,
                 step * static_cast<float>(j), 1.0f},
      }};

      this->triangles.push_back(t);

      Triangle t2{{
          Vertex{step * static_cast<float>(i), 0.0f,
                 step * static_cast<float>(j + 1), 1.0f},
          Vertex{step * static_cast<float>(i + 1), 0.0f,
                 step * static_cast<float>(j + 1), 1.0f},
          Vertex{step * static_cast<float>(i + 1), 0.0f,
                 step * static_cast<float>(j), 1.0f},
      }};
      this->triangles.push_back(t2);
    }
  }

  float translate = dimension / 2.0f;
  Matrix m = utils::translate(Matrix(1.0f),
                              Vertex{-translate, 0.0f, -translate, 0.0f});
  for (auto &triangle : this->triangles) {
    for (auto &vertice : triangle.vertices) {
      vertice = vertice * m;
    }
  }
}
