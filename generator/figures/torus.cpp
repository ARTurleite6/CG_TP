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

    float cur_alpha = bigger_step * static_cast<float>(i);
    float next_alpha = bigger_step * static_cast<float>(i + 1);

    for (int j = 0; j < number_stacks; ++j) {

      float cur_delta = smaller_step * static_cast<float>(j);
      float next_delta = smaller_step * static_cast<float>(j + 1);

      Triangle t1{std::array<Vertex, 3>{

          Vertex{
              (raio_maior + std::cos(cur_alpha) * raio_menor) *
                  std::sin(cur_delta),
              std::sin(cur_alpha) * raio_menor,
              (raio_maior + std::cos(cur_alpha) * raio_menor) *
                  std::cos(cur_delta),
              1.0f,
          },

          Vertex{
              (raio_maior + std::cos(cur_alpha) * raio_menor) *
                  std::sin(next_delta),
              std::sin(cur_alpha) * raio_menor,
              (raio_maior + std::cos(cur_alpha) * raio_menor) *
                  std::cos(next_delta),
              1.0f,
          },

          Vertex{
              (raio_maior + std::cos(next_alpha) * raio_menor) *
                  std::sin(next_delta),
              std::sin(next_alpha) * raio_menor,
              (raio_maior + std::cos(next_alpha) * raio_menor) *
                  std::cos(next_delta),
              1.0f,
          },
      }};

      Triangle t2{std::array<Vertex, 3>{

          Vertex{
              (raio_maior + std::cos(cur_alpha) * raio_menor) *
                  std::sin(cur_delta),
              std::sin(cur_alpha) * raio_menor,
              (raio_maior + std::cos(cur_alpha) * raio_menor) *
                  std::cos(cur_delta),
              1.0f,
          },

          Vertex{
              (raio_maior + std::cos(next_alpha) * raio_menor) *
                  std::sin(next_delta),
              std::sin(next_alpha) * raio_menor,
              (raio_maior + std::cos(next_alpha) * raio_menor) *
                  std::cos(next_delta),
              1.0f,
          },

          Vertex{
              (raio_maior + std::cos(next_alpha) * raio_menor) *
                  std::sin(cur_delta),
              std::sin(next_alpha) * raio_menor,
              (raio_maior + std::cos(next_alpha) * raio_menor) *
                  std::cos(cur_delta),
              1.0f,
          },

      }};

      this->triangles.push_back(t1);
      this->triangles.push_back(t2);
    }
  }
}
