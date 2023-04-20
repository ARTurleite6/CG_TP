#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "my_math.h"

using namespace maths;

struct Triangle {
  std::array<Vertex, 3> vertices;

  explicit Triangle(const std::array<Vertex, 3> &vertices)
      : vertices(vertices) {}
};

#endif
