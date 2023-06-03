#include "Plane.h"

Plane::Plane(const std::vector<float> &args)
    : Figure(args), dimension(args[0]), divisions(args[1]) {

  float step = dimension / divisions;

  int N = static_cast<int>(divisions);
  float texStep = 1.0f / static_cast<float>(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {

      this->vertices.emplace_back(dimension - (step * static_cast<float>(i)),
                                  0.0f, step * static_cast<float>(j), 1.0f);
      this->vertices.emplace_back(dimension -
                                      (step * static_cast<float>(i + 1)),
                                  0.0f, step * static_cast<float>(j), 1.0f);
      this->vertices.emplace_back(dimension - (step * static_cast<float>(i)),
                                  0.0f, step * static_cast<float>(j + 1), 1.0f);

      for (int k = 0; k < 3; ++k) {
        this->normals.emplace_back(0.0f, 1.0f, 0.0f, 0.0f);
      }

      this->vertices.emplace_back(dimension -
                                      (step * static_cast<float>(i + 1)),
                                  0.0f, step * static_cast<float>(j), 1.0f);
      this->vertices.emplace_back(dimension -
                                      (step * static_cast<float>(i + 1)),
                                  0.0f, step * static_cast<float>(j + 1), 1.0f);
      this->vertices.emplace_back(dimension - (step * static_cast<float>(i)),
                                  0.0f, step * static_cast<float>(j + 1), 1.0f);

      for (int k = 0; k < 3; ++k) {
        this->normals.emplace_back(0.0f, 1.0f, 0.0f, 0.0f);
      }

      this->texCoords.emplace_back(texStep * static_cast<float>(i),
                                   texStep * static_cast<float>(j));

      this->texCoords.emplace_back(texStep * static_cast<float>(i + 1),
                                   texStep * static_cast<float>(j));

      this->texCoords.emplace_back(texStep * static_cast<float>(i),
                                   texStep * static_cast<float>(j + 1));

      this->texCoords.emplace_back(texStep * static_cast<float>(i + 1),
                                   texStep * static_cast<float>(j));

      this->texCoords.emplace_back(texStep * static_cast<float>(i + 1),
                                   texStep * static_cast<float>(j + 1));

      this->texCoords.emplace_back(texStep * static_cast<float>(i),
                                   texStep * static_cast<float>(j + 1));
    }
  }

  float translate = dimension / 2.0f;
  auto m = maths::rotate(maths::Matrix(1.0f),
                         maths::Vertex{0.0f, 1.0f, 0.0f, 0.0f}, 180.0f) *
           maths::translate(maths::Matrix(1.0f),
                            Vertex{-translate, 0.0f, -translate, 0.0f});
  this->computeOperation(m);
}

void Plane::computeTextureCoords(float minS, float maxS, float minT,
                                 float maxT) {

  for (auto &coord : this->texCoords) {
    auto prevX = coord.getX();
    auto prevY = coord.getY();

    auto s = maths::withinRange(prevX, minS, maxS);
    auto t = maths::withinRange(prevY, minT, maxT);

    coord.setX(s);
    coord.setY(t);
  }
}
