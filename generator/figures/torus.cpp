#include "torus.h"

Torus::Torus(const std::vector<float> &args) {
  raio_maior = args[0];
  raio_menor = args[1];
  number_stacks = static_cast<std::uint32_t>(args[2]);
  number_slices = static_cast<std::uint32_t>(args[3]);

  float bigger_step =
      std::numbers::pi_v<float> * 2 / static_cast<float>(number_slices);
  float smaller_step =
      std::numbers::pi_v<float> * 2 / static_cast<float>(number_stacks);

  for (int i = 0; i < number_slices; ++i) {

    float alpha_angle = bigger_step * static_cast<float>(i);
    float next_alpha_angle = bigger_step * static_cast<float>(i + 1);

    for (int j = 0; j < number_stacks; ++j) {

      float delta_angle = smaller_step * static_cast<float>(j);
      float next_delta_angle = smaller_step * static_cast<float>(j + 1);

      Triangle t1{std::array<Vertex, 3>{
          Vertex{(this->raio_maior +
                  this->raio_menor * std::cos(next_delta_angle)) *
                     std::sin(alpha_angle),
                 (this->raio_menor * std::sin(next_delta_angle)),
                 (this->raio_maior +
                  this->raio_menor * std::cos(next_delta_angle)) *
                     std::sin(alpha_angle),
                 1.0f},
          Vertex{(this->raio_maior + this->raio_menor * std::cos(delta_angle)) *
                     std::sin(alpha_angle),
                 (this->raio_menor * std::sin(delta_angle)),
                 (this->raio_maior + this->raio_menor * std::cos(delta_angle)) *
                     std::sin(alpha_angle),
                 1.0f},
          Vertex{(this->raio_maior + this->raio_menor * std::cos(delta_angle)) *
                     std::sin(next_alpha_angle),
                 (this->raio_menor * std::sin(delta_angle)),
                 (this->raio_maior + this->raio_menor * std::cos(delta_angle)) *
                     std::sin(next_alpha_angle),
                 1.0f},
      }};

      Triangle t2{std::array<Vertex, 3>{
          Vertex{(this->raio_maior +
                  this->raio_menor * std::cos(next_delta_angle)) *
                     std::sin(alpha_angle),
                 (this->raio_menor * std::sin(next_delta_angle)),
                 (this->raio_maior +
                  this->raio_menor * std::cos(next_delta_angle)) *
                     std::sin(alpha_angle),
                 1.0f},
          Vertex{(this->raio_maior + this->raio_menor * std::cos(delta_angle)) *
                     std::sin(next_alpha_angle),
                 (this->raio_menor * std::sin(delta_angle)),
                 (this->raio_maior + this->raio_menor * std::cos(delta_angle)) *
                     std::sin(next_alpha_angle),
                 1.0f},
          Vertex{(this->raio_maior +
                  this->raio_menor * std::cos(next_delta_angle)) *
                     std::sin(next_alpha_angle),
                 (this->raio_menor * std::sin(next_delta_angle)),
                 (this->raio_maior +
                  this->raio_menor * std::cos(next_delta_angle)) *
                     std::sin(next_alpha_angle),
                 1.0f},
      }};

      this->triangles.push_back(t1);
      this->triangles.push_back(t2);
    }
  }
}
