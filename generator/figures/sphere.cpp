#include "sphere.h"

Sphere::Sphere(const std::vector<float> &args)
    : Figure(args), radius(args[0]), slices(args[1]), stacks(args[2]) {

  float xz_step = 2.0f * std::numbers::pi_v<float> / slices;
  float y_step = std::numbers::pi_v<float> / stacks;

  int stacks_n = static_cast<int>(this->stacks);
  int slices_n = static_cast<int>(this->slices);

  float tex_step_y = 1.0f / static_cast<float>(stacks_n);
  float tex_step_x = 1.0f / static_cast<float>(slices_n);

  for (int i = 0; i < stacks_n; ++i) {
    float current_sin = std::sin(y_step * static_cast<float>(i));
    float next_sin = std::sin(y_step * static_cast<float>(i + 1));

    for (int j = 0; j < slices_n; ++j) {

      this->vertices.emplace_back(
          this->radius * next_sin * std::sin(xz_step * static_cast<float>(j)),
          -this->radius * std::cos(y_step * static_cast<float>(i + 1)),
          this->radius * next_sin * std::cos(xz_step * static_cast<float>(j)),
          1.0f);

      this->normals.emplace_back(
          next_sin * std::sin(xz_step * static_cast<float>(j)),
          -std::cos(y_step * static_cast<float>(i + 1)),
          next_sin * std::cos(xz_step * static_cast<float>(j)), 0.0f);

      this->texCoords.emplace_back(tex_step_x * static_cast<float>(j),
                                   tex_step_y * (static_cast<float>(i + 1)));

      this->vertices.emplace_back(this->radius * current_sin *
                                      std::sin(xz_step * static_cast<float>(j)),
                                  -this->radius *
                                      std::cos(y_step * static_cast<float>(i)),
                                  this->radius * current_sin *
                                      std::cos(xz_step * static_cast<float>(j)),
                                  1.0f);
      this->normals.emplace_back(
          current_sin * std::sin(xz_step * static_cast<float>(j)),
          -std::cos(y_step * static_cast<float>(i)),
          current_sin * std::cos(xz_step * static_cast<float>(j)), 0.0f);

      this->texCoords.emplace_back(tex_step_x * static_cast<float>(j),
                                   tex_step_y * (static_cast<float>(i)));

      this->vertices.emplace_back(
          this->radius * current_sin *
              std::sin(xz_step * static_cast<float>(j + 1)),
          -this->radius * std::cos(y_step * static_cast<float>(i)),
          this->radius * current_sin *
              std::cos(xz_step * static_cast<float>(j + 1)),
          1.0f);
      this->normals.emplace_back(
          current_sin * std::sin(xz_step * static_cast<float>(j + 1)),
          -std::cos(y_step * static_cast<float>(i)),
          current_sin * std::cos(xz_step * static_cast<float>(j + 1)), 0.0f);

      this->texCoords.emplace_back(tex_step_x * static_cast<float>(j + 1),
                                   tex_step_y * (static_cast<float>(i)));

      this->vertices.emplace_back(
          this->radius * next_sin *
              std::sin(xz_step * static_cast<float>(j + 1)),
          -this->radius * std::cos(y_step * static_cast<float>(i + 1)),
          this->radius * next_sin *
              std::cos(xz_step * static_cast<float>(j + 1)),
          1.0f);
      this->normals.emplace_back(
          next_sin * std::sin(xz_step * static_cast<float>(j + 1)),
          -std::cos(y_step * static_cast<float>(i + 1)),
          next_sin * std::cos(xz_step * static_cast<float>(j + 1)), 0.0f);

      this->texCoords.emplace_back(tex_step_x * static_cast<float>(j + 1),
                                   tex_step_y * (static_cast<float>(i + 1)));

      this->vertices.emplace_back(
          this->radius * next_sin * std::sin(xz_step * static_cast<float>(j)),
          -this->radius * std::cos(y_step * static_cast<float>(i + 1)),
          this->radius * next_sin * std::cos(xz_step * static_cast<float>(j)),
          1.0f);
      this->normals.emplace_back(
          next_sin * std::sin(xz_step * static_cast<float>(j)),
          -std::cos(y_step * static_cast<float>(i + 1)),
          next_sin * std::cos(xz_step * static_cast<float>(j)), 0.0f);
      this->texCoords.emplace_back(tex_step_x * static_cast<float>(j),
                                   tex_step_y * (static_cast<float>(i + 1)));

      this->vertices.emplace_back(
          this->radius * current_sin *
              std::sin(xz_step * static_cast<float>(j + 1)),
          -this->radius * std::cos(y_step * static_cast<float>(i)),
          this->radius * current_sin *
              std::cos(xz_step * static_cast<float>(j + 1)),
          1.0f);
      this->normals.emplace_back(
          current_sin * std::sin(xz_step * static_cast<float>(j + 1)),
          -std::cos(y_step * static_cast<float>(i)),
          current_sin * std::cos(xz_step * static_cast<float>(j + 1)), 0.0f);
      this->texCoords.emplace_back(tex_step_x * static_cast<float>(j + 1),
                                   tex_step_y * (static_cast<float>(i)));
    }
  }

}
