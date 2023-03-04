#include "sphere.h"
#include <cmath>

Sphere::Sphere(const std::vector<float> &args)
    : Figure(args), radius(args[0]), slices(args[1]), stacks(args[2]) {

  float xz_step = 2.0f * std::numbers::pi_v<float> / slices;
  float y_step = std::numbers::pi_v<float> / stacks;

  int stacks_n = static_cast<int>(this->stacks);
  int slices_n = static_cast<int>(this->slices);

  for (int i = 0; i < stacks_n; ++i) {
    for (int j = 0; j < slices_n; ++j) {

      Triangle t1{
          std::array<float, 3>{
              this->radius * std::sin(xz_step * static_cast<float>(j)),
              this->radius * std::sin(y_step * static_cast<float>(i)),
              this->radius * std::cos(xz_step * static_cast<float>(j))},
          std::array<float, 3>{
              this->radius * std::sin(xz_step * static_cast<float>(j)),
              this->radius * std::sin(y_step * static_cast<float>(i + 1)),
              this->radius * std::cos(xz_step * static_cast<float>(j))},
          std::array<float, 3>{
              this->radius * std::sin(xz_step * static_cast<float>(j)),
              this->radius * std::sin(y_step * static_cast<float>(i)),
              this->radius * std::cos(xz_step * static_cast<float>(j + 1))},
      };

      Triangle t2{
          std::array<float, 3>{},
          std::array<float, 3>{},
          std::array<float, 3>{},
      };
    }
  }
}
