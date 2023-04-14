#ifndef UTILS_H
#define UTILS_H
#include <cmath>

namespace utils {

struct Matrix;

struct Vertex {
  Vertex() = default;
  Vertex(float x, float y, float z, float w);
  Vertex(Vertex &&) = default;
  Vertex(const Vertex &) = default;
  Vertex &operator=(Vertex &&) = default;
  Vertex &operator=(const Vertex &) = default;
  Vertex &operator*(const Matrix &m) noexcept;
  Vertex operator+(const Vertex &m) const noexcept;
  Vertex operator-(const Vertex &) const noexcept;
  Vertex &operator*(float constant) noexcept;
  [[nodiscard]]Vertex crossProduct(const Vertex &) const noexcept;
  ~Vertex() = default;
  void normalize() noexcept;

  float x, y, z, w;
};

struct Matrix {
  Matrix() = default;
  explicit Matrix(float x) noexcept;
  Matrix(Matrix &&) = default;
  Matrix(const Matrix &) = default;
  Matrix &operator=(Matrix &&) = default;
  Matrix &operator=(const Matrix &) = default;
  const std::array<float, 4> &operator[](int i) const noexcept;
  ~Matrix() = default;

  Matrix &operator*(const Matrix &m) noexcept; // ainda não está feito

  std::array<std::array<float, 4>, 4> m;
};

Matrix translate(const Matrix &m, const Vertex &v) noexcept;
Matrix scale(const Matrix &m, const Vertex &v) noexcept;
Matrix rotate(const Matrix &m, const Vertex &v, float angle) noexcept;

}; // namespace utils

// template <> std::is_swappable_v<utils::Vertex>{
// };

#endif
