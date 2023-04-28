#include "box.h"

Box::Box(const std::vector<float> &args) noexcept
    : dimensions(args[0]), divisions(args[1]) {

  std::array<Plane, 6> planes{Plane{args}, Plane{args}, Plane{args},
                              Plane{args}, Plane{args}, Plane{args}};

  // planes[0] base
  planes[0].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{0.0f, -dimensions / 2.0f, 0.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f}, 180.0f));

  planes[1].computeOperation(maths::translate(
      Matrix(1.0f), Vertex{0.0f, dimensions / 2.0f, 0.0f, 0.0f}));

  planes[2].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{0.0f, 0.0f, dimensions / 2.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f}, 90.0f));

  planes[3].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{0.0f, 0.0f, -dimensions / 2.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f}, -90.0f));

  planes[4].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{dimensions / 2.0f, 0.0f, 0.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 0.0f, 1.0f, 0.0f}, -90.0f));

  planes[5].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{-dimensions / 2.0f, 0.0f, 0.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 0.0f, -1.0f, 0.0f}, 90.0f));

  for (const auto &plane : planes) {
    for (const auto &triangle : plane.vertices)
      this->vertices.push_back(triangle);
    for (const auto &normal : plane.normals) {
      this->normals.push_back(normal);
    }
  }
}
