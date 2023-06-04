#include "cone.h"
#include <algorithm>

Cone::Cone(const std::vector<float> &data)
    : Figure(data), radius(data[0]), height(data[1]), slices(data[2]),
      stacks(data[3]) {

  int slices_n = static_cast<int>(slices);

  // Base
  float xz_angle = std::numbers::pi_v<float> * 2.0f / slices;

  for (int i = 0; i < slices_n; ++i) {

    this->vertices.emplace_back(0.0f, 0.0f, 0.0f, 1.0f);
    this->normals.emplace_back(0.0f, -1.0f, 0.0f, 0.0f);
    this->texCoords.emplace_back(0.0f, 0.0f);

    this->vertices.emplace_back(
        radius * std::sin(xz_angle * static_cast<float>(i)), 0.0f,
        radius * std::cos(xz_angle * static_cast<float>(i)), 1.0f);
    this->normals.emplace_back(0.0f, -1.0f, 0.0f, 0.0f);
    this->texCoords.emplace_back(0.0f, 0.0f);

    this->vertices.emplace_back(
        radius * std::sin(xz_angle * static_cast<float>(i - 1)), 0.0f,
        radius * std::cos(xz_angle * static_cast<float>(i - 1)), 1.0f);
    this->normals.emplace_back(0.0f, -1.0f, 0.0f, 0.0f);
    this->texCoords.emplace_back(0.0f, 0.0f);
  }

  int stack_n = static_cast<int>(stacks);
  float height_factor = height / stacks;
  float radius_factor = radius / stacks;
  float tex_slice_factor = 1.0f / slices;
  float tex_height_factor = 1.0f / stacks;

  float beta = std::atan(radius / height);

  for (int i = 0; i < stack_n; ++i) {
    float current_radius = radius_factor * static_cast<float>(i);
    float current_height = height_factor * (stacks - static_cast<float>(i));
    float next_radius = radius_factor * static_cast<float>(i + 1);
    float next_height = height_factor * (stacks - (static_cast<float>(i + 1)));
    auto currentTexT = tex_slice_factor * static_cast<float>(i);
    auto nextTexT = tex_slice_factor * static_cast<float>(i + 1);
    for (int j = 0; j < slices_n; ++j) {
      auto currentTexS = tex_slice_factor * static_cast<float>(j);
      auto nextTexS = tex_slice_factor * static_cast<float>(j + 1);

      this->vertices.emplace_back(
          current_radius * std::sin(xz_angle * static_cast<float>(j)),
          current_height,
          current_radius * std::cos(xz_angle * static_cast<float>(j)), 1.0f);

      this->normals.emplace_back(
          std::sin(xz_angle) * static_cast<float>(j) * std::cos(beta),
          std::sin(beta),
          std::cos(xz_angle) * static_cast<float>(j) * std::cos(beta), 0.0f);
      this->texCoords.emplace_back(currentTexS, currentTexT);

      this->vertices.emplace_back(
          next_radius * std::sin(xz_angle * static_cast<float>(j)), next_height,
          next_radius * std::cos(xz_angle * static_cast<float>(j)), 1.0f);

      this->normals.emplace_back(
          std::sin(xz_angle) * static_cast<float>(j) * std::cos(beta),
          std::sin(beta),
          std::cos(xz_angle) * static_cast<float>(j) * std::cos(beta), 0.0f);

      this->texCoords.emplace_back(currentTexS, nextTexT);

      this->vertices.emplace_back(
          next_radius * std::sin(xz_angle * static_cast<float>(1 + j)),
          next_height,
          next_radius * std::cos(xz_angle * static_cast<float>(1 + j)), 1.0f);

      this->normals.emplace_back(
          std::sin(xz_angle) * static_cast<float>(1 + j) * std::cos(beta),
          std::sin(beta),
          std::cos(xz_angle) * static_cast<float>(1 + j) * std::cos(beta),
          0.0f);
      this->texCoords.emplace_back(nextTexS, nextTexT);

      this->vertices.emplace_back(
          current_radius * std::sin(xz_angle * static_cast<float>(j)),
          current_height,
          current_radius * std::cos(xz_angle * static_cast<float>(j)), 1.0f);

      this->normals.emplace_back(
          std::sin(xz_angle) * static_cast<float>(j) * std::cos(beta),
          std::sin(beta),
          std::cos(xz_angle) * static_cast<float>(j) * std::cos(beta), 0.0f);
      this->texCoords.emplace_back(currentTexS, currentTexT);

      this->vertices.emplace_back(
          next_radius * std::sin(xz_angle * static_cast<float>(1 + j)),
          next_height,
          next_radius * std::cos(xz_angle * static_cast<float>(1 + j)), 1.0f);
      this->normals.emplace_back(
          std::sin(xz_angle) * static_cast<float>(j + 1) * std::cos(beta),
          std::sin(beta),
          std::cos(xz_angle) * static_cast<float>(j + 1) * std::cos(beta),
          0.0f);
      this->texCoords.emplace_back(nextTexS, nextTexT);

      this->vertices.emplace_back(
          current_radius * std::sin(xz_angle * static_cast<float>(j + 1)),
          current_height,
          current_radius * std::cos(xz_angle * static_cast<float>(j + 1)),
          1.0f);
      this->normals.emplace_back(
          std::sin(xz_angle) * static_cast<float>(j + 1) * std::cos(beta),
          std::sin(beta),
          std::cos(xz_angle) * static_cast<float>(j + 1) * std::cos(beta),
          0.0f);
      this->texCoords.emplace_back(nextTexS, currentTexT);
    }
  }
}
