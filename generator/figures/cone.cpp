#include "cone.h"

Cone::Cone(const std::vector<float> &data)
    : Figure(data), radius(data[0]), height(data[1]), slices(data[2]),
      stacks(data[3]) {

  int slices_n = static_cast<int>(slices);

  // Base
  float xz_angle = std::numbers::pi_v<float> * 2.0f / slices;

  for (int i = 0; i < slices_n; ++i) {

    Triangle t1{std::array<Vertex, 3>{
        Vertex{
            0.0f,
            0.0f,
            0.0f,
            1.0f,
        },
        Vertex{
            radius * std::sin(xz_angle * static_cast<float>(i)),
            0.0f,
            radius * std::cos(xz_angle * static_cast<float>(i)),
            1.0f,
        },
        Vertex{
            radius * std::sin(xz_angle * static_cast<float>(i - 1)),
            0.0f,
            radius * std::cos(xz_angle * static_cast<float>(i - 1)),
            1.0f,
        },
    }};

    this->triangles.push_back(t1);
  }

  int stack_n = static_cast<int>(stacks);
  float height_factor = height / stacks;
  float radius_factor = radius / stacks;

  for (int i = 0; i < stack_n; ++i) {
    float current_radius = radius_factor * static_cast<float>(i);
    float current_height = height_factor * (stacks - static_cast<float>(i));
    float next_radius = radius_factor * static_cast<float>(i + 1);
    float next_height = height_factor * (stacks - (static_cast<float>(i + 1)));
    for (int j = 0; j < slices_n; ++j) {

      Triangle t1{std::array<Vertex, 3>{
          Vertex{current_radius * std::sin(xz_angle * static_cast<float>(j)),
                 current_height,
                 current_radius * std::cos(xz_angle * static_cast<float>(j)),
                 1.0f},
          Vertex{next_radius * std::sin(xz_angle * static_cast<float>(j)),
                 next_height,
                 next_radius * std::cos(xz_angle * static_cast<float>(j)),
                 1.0f},
          Vertex{next_radius * std::sin(xz_angle * static_cast<float>(1 + j)),
                 next_height,
                 next_radius * std::cos(xz_angle * static_cast<float>(1 + j)),
                 1.0f},
      }};

      Triangle t2{std::array<Vertex, 3>{
          Vertex{current_radius * std::sin(xz_angle * static_cast<float>(j)), current_height,
                 current_radius * std::cos(xz_angle * static_cast<float>(j)), 1.0f},
          Vertex{next_radius * std::sin(xz_angle * static_cast<float>(1 + j)), next_height,
                 next_radius * std::cos(xz_angle * static_cast<float>(1 + j)), 1.0f},
          Vertex{current_radius * std::sin(xz_angle * static_cast<float>(j + 1)), current_height,
                 current_radius * std::cos(xz_angle * static_cast<float>(j + 1)), 1.0f},
      }};

      this->triangles.push_back(t1);
      this->triangles.push_back(t2);
    }
  }
}