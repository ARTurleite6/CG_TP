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

Matrix rotate(const Matrix &m, const Vertex &v, float angle) noexcept {

  Matrix result = m;

  if (v.x != 0.0f) {
    result.m[1][1] = std::cos(angle);
    result.m[1][2] = -std::sin(angle);
    result.m[2][1] = std::sin(angle);
    result.m[2][2] = std::cos(angle);
  } else if (v.y != 0.0f) {
    result.m[0][0] = std::cos(angle);
    result.m[0][2] = std::sin(angle);
    result.m[2][0] = -std::sin(angle);
    result.m[2][2] = std::cos(angle);
  } else if (v.z != 0.0f) {
    result.m[0][0] = std::cos(angle);
    result.m[0][1] = -std::sin(angle);
    result.m[1][0] = std::sin(angle);
    result.m[1][1] = std::cos(angle);
  }

  return result;
}

Vertex &Vertex::operator*(const Matrix &m) noexcept {

  const Vertex v = *this;

  this->x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
  this->y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
  this->z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
  this->w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

  return *this;
}

const std::array<float, 4> &Matrix::operator[](int i) const noexcept {
  return this->m[i];
}

Matrix &Matrix::operator*(const Matrix &m) noexcept {

  const Matrix v = *this;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      this->m[i][j] = 0.0f;
      for (int k = 0; k < 4; k++) {
        this->m[i][j] += v.m[i][k] * m.m[k][j];
      }
    }
  }

  return *this;
}

}; // namespace utils
