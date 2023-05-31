#include "Plane.h"

Plane::Plane(const std::vector<float> &args)
    : Figure(args), dimension(args[0]), divisions(args[1]) {
  std::cout << "computePlane()\n";
  std::cout << "args: " << dimension << ' ' << divisions << '\n';

  float step = dimension / divisions;
  std::cout << "step = " << step << '\n';

  float texStep = 1.0f / divisions;

  int N = static_cast<int>(divisions);
  std::cout << "N = " << N << '\n';
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {

      this->vertices.emplace_back(step * static_cast<float>(i), 0.0f,
                                  step * static_cast<float>(j), 1.0f);
      this->vertices.emplace_back(step * static_cast<float>(i), 0.0f,
                                  step * static_cast<float>(j + 1), 1.0f);
      this->vertices.emplace_back(step * static_cast<float>(i + 1), 0.0f,
                                  step * static_cast<float>(j), 1.0f);

      for (int k = 0; k < 3; ++k) {
        this->normals.emplace_back(0.0f, 1.0f, 0.0f, 0.0f);
      }

      this->vertices.emplace_back(step * static_cast<float>(i), 0.0f,
                                  step * static_cast<float>(j + 1), 1.0f);
      this->vertices.emplace_back(step * static_cast<float>(i + 1), 0.0f,
                                  step * static_cast<float>(j + 1), 1.0f);
      this->vertices.emplace_back(step * static_cast<float>(i + 1), 0.0f,
                                  step * static_cast<float>(j), 1.0f);

      for (int k = 0; k < 3; ++k) {
        this->normals.emplace_back(0.0f, 1.0f, 0.0f, 0.0f);
      }

      this->texCoords.emplace_back(texStep * static_cast<float>(i),
                                   texStep * static_cast<float>(j));

      this->texCoords.emplace_back(texStep * static_cast<float>(i),
                                   texStep * static_cast<float>(j + 1));

      this->texCoords.emplace_back(texStep * static_cast<float>(i + 1),
                                   texStep * static_cast<float>(j));

      this->texCoords.emplace_back(texStep * static_cast<float>(i),
                                   texStep * static_cast<float>(j + 1));

      this->texCoords.emplace_back(texStep * static_cast<float>(i + 1),
                                   texStep * static_cast<float>(j + 1));

      this->texCoords.emplace_back(texStep * static_cast<float>(i + 1),
                                   texStep * static_cast<float>(j));
    }
  }

  float translate = dimension / 2.0f;
  auto m = maths::translate(maths::Matrix(1.0f),
                            Vertex{-translate, 0.0f, -translate, 0.0f});
  for (auto &vertice : this->vertices) {
    vertice = vertice * m;
  }
}
