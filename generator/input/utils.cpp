#include "utils.h"
#include <cmath>

namespace utils {
Vertex::Vertex(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Matrix::Matrix(float x) noexcept
    : m{std::array<float, 4>{x, 0.0f, 0.0f, 0.0f},
        std::array<float, 4>{0.0f, x, 0.0f, 0.0f},
        std::array<float, 4>{0.0f, 0.0f, x, 0.0f},
        std::array<float, 4>{0.0f, 0.0f, 0.0f, x}} {}

Matrix translate(const Matrix &m, const Vertex &v) noexcept {
  Matrix result = m;

  result.m[0][3] = v.x;
  result.m[1][3] = v.y;
  result.m[2][3] = v.z;

  return result;
}

Matrix scale(const Matrix &m, const Vertex &v) noexcept {
  Matrix result = m;

  result.m[0][0] = v.x;
  result.m[1][1] = v.y;
  result.m[2][2] = v.z;

  return result;
}

Vertex Matrix::operator*(const Vertex &v) const noexcept {
  return {
      m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
      m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
      m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
      m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w,
  };
}

Matrix rotate(const Matrix &m, const Vertex &v) noexcept {

  Matrix result = m;

  if (v.x != 0.0f) {
    result.m[1][1] = std::cos(v.x);
    result.m[1][2] = -std::sin(v.x);
    result.m[2][1] = std::sin(v.x);
    result.m[2][2] = std::cos(v.x);
  } else if (v.y != 0.0f) {
    result.m[0][0] = std::cos(v.y);
    result.m[0][2] = std::sin(v.y);
    result.m[2][0] = -std::sin(v.y);
    result.m[2][2] = std::cos(v.y);
  } else if (v.z != 0.0f) {
    result.m[0][0] = std::cos(v.z);
    result.m[0][1] = -std::sin(v.z);
    result.m[1][0] = std::sin(v.z);
    result.m[1][1] = std::cos(v.z);
  }

  return result;
}

Matrix &Matrix::operator*(const Matrix &m) const noexcept {

    return *this;
}; // namespace utils
