#ifndef UTILS_H
#define UTILS_H
#include <array>

namespace utils {

struct Vertex {
  Vertex() = default;
  Vertex(float x, float y, float z, float w);
  Vertex(Vertex &&) = default;
  Vertex(const Vertex &) = default;
  Vertex &operator=(Vertex &&) = default;
  Vertex &operator=(const Vertex &) = default;
  ~Vertex() = default;
  float x, y, z, w;
};

struct Matrix {
  Matrix() = default;
  explicit Matrix(float x) noexcept;
  Matrix(Matrix &&) = default;
  Matrix(const Matrix &) = default;
  Matrix &operator=(Matrix &&) = default;
  Matrix &operator=(const Matrix &) = default;
  ~Matrix() = default;

  Vertex &operator*(const Vertex &v) const noexcept;
  Matrix &operator*(Matrix &m) const noexcept;

  std::array<std::array<float, 4>, 4> m;
};

Matrix translate(const Matrix &m, const Vertex &v) noexcept;
Matrix scale(const Matrix &m, const Vertex &v) noexcept;
Matrix rotate(const Matrix &m, const Vertex &v) noexcept;

}; // namespace utils

#endif
