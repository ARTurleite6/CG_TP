#include "box.h"

Box::Box(const std::vector<float> &args) noexcept
    : dimensions(args[0]), divisions(args[1]) {

  std::array<Plane, 6> planes{Plane{args}, Plane{args}, Plane{args},
                              Plane{args}, Plane{args}, Plane{args}};

  // planes[0] base
  planes[0].computeOperation(utils::translate(
      Matrix(1.0f), Vertex{0.0f, -dimensions / 2.0f, 0.0f, 0.0f}));

  planes[1].computeOperation(utils::translate(
      Matrix(1.0f), Vertex{0.0f, dimensions / 2.0f, 0.0f, 0.0f}));

  planes[2].computeOperation(utils::translate(
      Matrix(1.0f), Vertex{0.0f, 0.0f, dimensions / 2.0f, 0.0f}) * utils::rotate(Matrix(1.0f),
                                           Vertex{1.0f, 0.0f, 0.0f, 0.0f},
                                           std::numbers::pi_v<float> / 2.0f));

  //planes[2].computeOperation(utils::translate(
  //    Matrix(1.0f), Vertex{0.0f, 0.0f, dimensions / 2.0f, 0.0f}));

  planes[3].computeOperation(utils::translate(
      Matrix(1.0f), Vertex{0.0f, 0.0f, -dimensions / 2.0f, 0.0f}) * utils::rotate(Matrix(1.0f),
                                           Vertex{1.0f, 0.0f, 0.0f, 0.0f},
                                           std::numbers::pi_v<float> / 2.0f));
  //planes[3].computeOperation(utils::translate(
  //    Matrix(1.0f), Vertex{0.0f, 0.0f, -dimensions / 2.0f, 0.0f}));

  planes[4].computeOperation(utils::translate(
      Matrix(1.0f), Vertex{dimensions / 2.0f, 0.0f, 0.0f, 0.0f}) * utils::rotate(Matrix(1.0f),
                                           Vertex{0.0f, 0.0f, 1.0f, 0.0f},
                                           std::numbers::pi_v<float> / 2.0f));

  //planes[4].computeOperation(utils::translate(
  //    Matrix(1.0f), Vertex{dimensions / 2.0f, 0.0f, 0.0f, 0.0f}));

  planes[5].computeOperation(utils::translate(
      Matrix(1.0f), Vertex{-dimensions / 2.0f, 0.0f, 0.0f, 0.0f})* utils::rotate(Matrix(1.0f),
                                           Vertex{0.0f, 0.0f, -1.0f, 0.0f},
                                           std::numbers::pi_v<float> / 2.0f));

  //planes[5].computeOperation(utils::translate(
  //    Matrix(1.0f), Vertex{-dimensions / 2.0f, 0.0f, 0.0f, 0.0f}));

  // planos virados para mim: 1, 2, 4, 5
  for (auto &t : planes[0].triangles) {
    std::reverse(t.vertices.begin(), t.vertices.end());
  }

  for (auto &t : planes[3].triangles) {
    std::reverse(t.vertices.begin(), t.vertices.end());
  }

  for (auto &t : planes[4].triangles) {
    std::reverse(t.vertices.begin(), t.vertices.end());
  }

  std::cout << "plane 3\n";
  for(const auto &t: planes[3].triangles) {
    for(const auto &v: t.vertices) {
      std::cout << v.x << " " << v.y << " " << v.z << std::endl;
    }
  }
  std::cout << "end\n";

  for (const auto &plane : planes)
    for (const auto &triangle : plane.triangles)
      this->triangles.push_back(triangle);
}
