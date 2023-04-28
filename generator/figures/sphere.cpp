#include "sphere.h"

Sphere::Sphere(const std::vector<float> &args)
    : Figure(args), radius(args[0]), slices(args[1]), stacks(args[2]) {

  std::cout << "Sphere constructor called\n";
  for (const auto &arg : args) {
    std::cout << arg << '\n';
  }

  float xz_step = 2.0f * std::numbers::pi_v<float> / slices;
  float y_step = std::numbers::pi_v<float> / stacks;

  int stacks_n = static_cast<int>(this->stacks);
  int slices_n = static_cast<int>(this->slices);

  std::cout << "stacks: " << stacks_n << '\n';
  std::cout << "slices: " << slices_n << '\n';

  for (int i = 0; i < stacks_n; ++i) {
    float current_radius_line =
        this->radius * std::sin(y_step * static_cast<float>(i));

    float next_radius_line =
        this->radius * std::sin(y_step * static_cast<float>(i + 1));
    for (int j = 0; j < slices_n; ++j) {

      this->vertices.emplace_back(
          next_radius_line * std::sin(xz_step * static_cast<float>(j)),
          this->radius * std::cos(y_step * static_cast<float>(i + 1)),
          next_radius_line * std::cos(xz_step * static_cast<float>(j)), 1.0f);
      this->normals.emplace_back(std::sin(xz_step * static_cast<float>(j)),
                                 std::cos(y_step * static_cast<float>(i + 1)),
                                 std::cos(xz_step * static_cast<float>(j)),
                                 0.0f);
      this->vertices.emplace_back(
          current_radius_line * std::sin(xz_step * static_cast<float>(j)),
          this->radius * std::cos(y_step * static_cast<float>(i)),
          current_radius_line * std::cos(xz_step * static_cast<float>(j)),
          1.0f);
      this->normals.emplace_back(std::sin(xz_step * static_cast<float>(j)),
                                 std::cos(y_step * static_cast<float>(i)),
                                 std::cos(xz_step * static_cast<float>(j)),
                                 0.0f);
      this->vertices.emplace_back(
          current_radius_line * std::sin(xz_step * static_cast<float>(j + 1)),
          this->radius * std::cos(y_step * static_cast<float>(i)),
          current_radius_line * std::cos(xz_step * static_cast<float>(j + 1)),
          1.0f);
      this->normals.emplace_back(std::sin(xz_step * static_cast<float>(j + 1)),
                                 std::cos(y_step * static_cast<float>(i)),
                                 std::cos(xz_step * static_cast<float>(j + 1)),
                                 0.0f);

      this->vertices.emplace_back(
          next_radius_line * std::sin(xz_step * static_cast<float>(j + 1)),
          this->radius * std::cos(y_step * static_cast<float>(i + 1)),
          next_radius_line * std::cos(xz_step * static_cast<float>(j + 1)),
          1.0f);
      this->normals.emplace_back(std::sin(xz_step * static_cast<float>(j + 1)),
                                 std::cos(y_step * static_cast<float>(i + 1)),
                                 std::cos(xz_step * static_cast<float>(j + 1)),
                                 0.0f);
      this->vertices.emplace_back(
          next_radius_line * std::sin(xz_step * static_cast<float>(j)),
          this->radius * std::cos(y_step * static_cast<float>(i + 1)),
          next_radius_line * std::cos(xz_step * static_cast<float>(j)), 1.0f);
      this->normals.emplace_back(std::sin(xz_step * static_cast<float>(j)),
                                 std::cos(y_step * static_cast<float>(i + 1)),
                                 std::cos(xz_step * static_cast<float>(j)),
                                 0.0f);
      this->vertices.emplace_back(
          current_radius_line * std::sin(xz_step * static_cast<float>(j + 1)),
          std::cos(y_step * static_cast<float>(i)),
          current_radius_line * std::cos(xz_step * static_cast<float>(j + 1)),
          1.0f);
      this->normals.emplace_back(std::sin(xz_step * static_cast<float>(j + 1)),
                                 std::cos(y_step * static_cast<float>(i)),
                                 std::cos(xz_step * static_cast<float>(j + 1)),
                                 0.0f);
    }
  }
}
