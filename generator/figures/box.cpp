#include "box.h"
#include <memory>

Box::Box(const std::vector<float> &args) noexcept
    : dimensions(args[0]), divisions(args[1]) {

  std::array<Plane, 6> planes{Plane{args}, Plane{args}, Plane{args},
                              Plane{args}, Plane{args}, Plane{args}};

  // bases
  auto translate_up_height =
      utils::translate(Matrix(1.0f), utils::Vertex{0.0f, args[0], 0.0f, 0.0f});

  // planes[0] base
  planes[1].computeOperation(
      utils::translate(Matrix(1.0f), Vertex{0.0f, dimensions, 0.0f, 0.0f}));

  planes[2].computeOperation(utils::rotate(
      Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f})); // rotate x

    planes[3].computeOperation(utils::rotate(

                ))
}
