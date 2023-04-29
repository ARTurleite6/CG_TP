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
  std::for_each(planes[0].normals.begin(), planes[0].normals.end(),
                [](Vertex &v) { v.y = -1; });

  planes[1].computeOperation(maths::translate(
      Matrix(1.0f), Vertex{0.0f, dimensions / 2.0f, 0.0f, 0.0f}));

  planes[2].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{0.0f, 0.0f, dimensions / 2.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f}, 90.0f));

  std::for_each(planes[2].normals.begin(), planes[2].normals.end(),
                [](Vertex &v) {
                  v.y = 0;
                  v.z = 1.0f;
                });

  planes[3].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{0.0f, 0.0f, -dimensions / 2.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f}, -90.0f));

  std::for_each(planes[3].normals.begin(), planes[3].normals.end(),
                [](Vertex &v) {
                  v.y = 0;
                  v.z = -1.0f;
                });

  planes[4].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{dimensions / 2.0f, 0.0f, 0.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 0.0f, 1.0f, 0.0f}, -90.0f));

  std::for_each(planes[4].normals.begin(), planes[4].normals.end(),
                [](Vertex &v) {
                  v.y = 0;
                  v.x = 1.0f;
                });

  planes[5].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{-dimensions / 2.0f, 0.0f, 0.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 0.0f, -1.0f, 0.0f}, 90.0f));

  std::for_each(planes[5].normals.begin(), planes[5].normals.end(),
                [](Vertex &v) {
                  v.y = 0;
                  v.x = -1.0f;
                });

  for (const auto &plane : planes) {
    for (const auto &triangle : plane.vertices)
      this->vertices.push_back(triangle);
    for (const auto &normal : plane.normals) {
      this->normals.push_back(normal);
    }
  }
}
