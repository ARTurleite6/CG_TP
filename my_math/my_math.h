#ifndef MY_MATH_H
#define MY_MATH_H
#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace maths {

struct Matrix;

struct Vertex {
  Vertex() = default;
  Vertex(float x, float y, float z, float w);
  Vertex(Vertex &&) = default;
  Vertex(const Vertex &) = default;
  Vertex &operator=(Vertex &&) = default;
  Vertex &operator=(const Vertex &) = default;
  Vertex &operator*(const Matrix &m) noexcept;
  Vertex operator*(float constant) const noexcept;
  Vertex operator+(const Vertex &m) const noexcept;
  Vertex operator-(const Vertex &) const noexcept;
  Vertex &operator*(float constant) noexcept;
  Vertex &operator+=(const Vertex &) noexcept;
  float operator*(const Vertex &) const noexcept;

  static Vertex fromSpherical(float radius, float alpha, float beta);

  [[nodiscard]] Vertex crossProduct(const Vertex &) const noexcept;
  ~Vertex() = default;
  void normalize() noexcept;

  float x{}, y{}, z{}, w{};
};

Vertex operator*(float x, const Vertex &vertex);


struct Matrix {
  Matrix() = default;
  explicit Matrix(std::array<std::array<float, 4>, 4> matrix);
  explicit Matrix(float x) noexcept;
  Matrix(Matrix &&) = default;
  Matrix(const Matrix &) = default;
  Matrix &operator=(Matrix &&) = default;
  Matrix &operator=(const Matrix &) = default;
  Vertex operator*(const Vertex &);
  const std::array<float, 4> &operator[](int i) const noexcept;
  ~Matrix() = default;

  Matrix &operator*(const Matrix &m) noexcept;

  static std::array<std::array<Vertex, 4>, 4>
  patchMatrix(const std::array<std::array<Vertex, 4>, 4> &mP);

    [[nodiscard]] Matrix transpose() const noexcept;

    std::array<std::array<float, 4>, 4> m{};
    template <class First, class Second, class Return, std::uint32_t LF,
              std::uint32_t M, std::uint32_t CS>
    static std::array<std::array<Return, CS>, LF> gen_multiply_matrix(
        const std::array<std::array<First, M>, LF> &first,
        const std::array<std::array<Second, CS>, M> &second) {

      std::array<std::array<Return, CS>, LF> res{};

      for (int i = 0; i < LF; ++i) {
        for (int j = 0; j < CS; ++j) {
          for (int w = 0; w < M; ++w) {
            res[i][j] += first[i][w] * second[w][j];
          }
        }
      }

      return res;
    }
  };

Matrix translate(const Matrix &m, const Vertex &v) noexcept;
Matrix scale(const Matrix &m, const Vertex &v) noexcept;
Matrix rotate(const Matrix &m, const Vertex &v, float angle) noexcept;


}; // namespace utils

// template <> std::is_swappable_v<utils::Vertex>{
// };

#endif
