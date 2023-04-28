#include "pyramid.h"

Pyramid::Pyramid(const std::vector<float> &args)
    : height(args[0]), slices(static_cast<std::uint32_t>(args[1])) {
  float step = std::numbers::pi_v<float> * 2 / static_cast<float>(slices);

  // top
  for (int i = 0; i < slices; ++i) {
    float angle = step * static_cast<float>(i);
    float next_angle = step * static_cast<float>(i + 1);
    float middle_height = height / 2;

    this->vertices.emplace_back(0.0f, middle_height, 0.0f, 1.0f);
    this->vertices.emplace_back(std::sin(angle), middle_height, std::cos(angle),
                                1.0f);
    this->vertices.emplace_back(std::sin(next_angle), middle_height,
                                std::cos(next_angle), 1.0f);
  }
  // base
  for (int i = 0; i < slices; ++i) {
    float angle = step * static_cast<float>(i);
    float next_angle = step * static_cast<float>(i + 1);
    float middle_height = height / 2;

    this->vertices.emplace_back(0.0f, -middle_height, 0.0f, 1.0f);
    this->vertices.emplace_back(-std::sin(angle), -middle_height,
                                std::cos(angle), 1.0f);
    this->vertices.emplace_back(-std::sin(next_angle), -middle_height,
                                std::cos(next_angle), 1.0f);
  }

  // sides
  for (int i = 0; i < slices; ++i) {

    float angle = step * static_cast<float>(i);
    float next_angle = step * static_cast<float>(i + 1);
    float middle_height = height / 2;

    this->vertices.emplace_back(std::sin(angle), middle_height, std::cos(angle),
                                1.0f);
    this->vertices.emplace_back(std::sin(angle), -middle_height,
                                std::cos(angle), 1.0f);
    this->vertices.emplace_back(std::sin(next_angle), -middle_height,
                                std::cos(next_angle), 1.0f);

    this->vertices.emplace_back(std::sin(angle), middle_height, std::cos(angle),
                                1.0f);
    this->vertices.emplace_back(std::sin(next_angle), -middle_height,
                                std::cos(next_angle), 1.0f);
    this->vertices.emplace_back(std::sin(next_angle), middle_height,
                                std::cos(next_angle), 1.0f);
  }
}
