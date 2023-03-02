#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "../input/utils.h"

using namespace utils;

struct Triangle {
  std::array<Vertex, 3> vertices;

  explicit Triangle(const std::array<Vertex, 3> &vertices)
      : vertices(vertices) {}
};

#endif
