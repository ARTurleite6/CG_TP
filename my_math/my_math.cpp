#include "my_math.h"

namespace maths {
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

Vertex Vertex::operator-(const Vertex &vertex) const noexcept {
  return Vertex{this->x - vertex.x, this->y - vertex.y, this->z - vertex.z,
                this->w - vertex.w};
}

void Vertex::normalize() noexcept {
  auto norm = std::sqrt(this->x * this->x + this->y * this->y +
                        this->z * this->z + this->w * this->w);

  this->x /= norm;
  this->y /= norm;
  this->z /= norm;
  this->w /= norm;
}

Vertex Vertex::operator+(const Vertex &m) const noexcept {
  return Vertex{
      this->x + m.x,
      this->y + m.y,
      this->z + m.z,
      this->w + m.w,
  };
}

Vertex operator*(const Vertex &v, float constant) noexcept {
  return { v.x * constant, v.y * constant, v.z * constant, v.w * constant };
}

[[nodiscard]] Vertex Vertex::crossProduct(const Vertex &v) const noexcept {

  return Vertex{
      this->y * v.z - this->z * v.y,
      this->z * v.x - this->x * v.z,
      this->x * v.y - this->y * v.x,
      0.0f,
  };
}

Vertex &Vertex::operator+=(const Vertex &v) noexcept {
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
  this->w += v.w;
  return *this;
}

Vertex Vertex::fromSpherical(float radius, float alpha, float beta) {
  return maths::Vertex{radius * std::sin(alpha) * std::cos(beta),
                       radius * std::sin(beta),
                       radius * std::cos(alpha) * std::cos(beta), 1.0f};
}

Matrix::Matrix(std::array<std::array<float, 4>, 4> matrix) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      this->m[i][j] = matrix[i][j];
    }
  }
}

Vertex Matrix::operator*(const Vertex &vertex) {
  maths::Vertex result;

  result.x = this->m[0][0] * vertex.x + this->m[0][1] * vertex.y +
             this->m[0][2] * vertex.z + this->m[0][3] * vertex.w;

  result.y = this->m[1][0] * vertex.x + this->m[1][1] * vertex.y +
             this->m[1][2] * vertex.z + this->m[1][3] * vertex.w;

  result.z = this->m[2][0] * vertex.x + this->m[2][1] * vertex.y +
             this->m[2][2] * vertex.z + this->m[2][3] * vertex.w;

  result.w = this->m[3][0] * vertex.x + this->m[3][1] * vertex.y +
             this->m[3][2] * vertex.z + this->m[3][3] * vertex.w;

  return result;
}

float Vertex::operator*(const Vertex &vertex) const noexcept {
  return this->x * vertex.x + this->y * vertex.y + this->z * vertex.z +
         this->w * vertex.w;
}

[[nodiscard]] Matrix Matrix::transpose() const noexcept {
  Matrix new_matrix;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      new_matrix.m[i][j] = this->m[j][i];
    }
  }

  return new_matrix;
}

std::array<std::array<Vertex, 4>, 4> Matrix::patchMatrix(const std::array<std::array<Vertex, 4>, 4> &mP) {
  Matrix m{std::array<std::array<float, 4>, 4>{
      std::array<float, 4>{-1.0f, +3.0f, -3.0f, +1.0f},
      std::array<float, 4>{+3.0f, -6.0f, +3.0f, +0.0f},
      std::array<float, 4>{-3.0f, +3.0f, +0.0f, +0.0f},
      std::array<float, 4>{+1.0f, +0.0f, +0.0f, +0.0f}}};


  auto temp = Matrix::gen_multiply_matrix<float, Vertex, Vertex, 4, 4, 4>(m.m, mP);
  auto transpose = m.transpose();
  std::cout << "size = " << transpose.m[0].size();
    for(const auto &arr : temp) {
        for(const auto value : arr) {
            std::cout << "x = " <<  value.x << ',';
            std::cout << "y = " <<  value.y << ',';
            std::cout << "z = " <<  value.z << ',';
        }
        std::cout << '\n';
    }
  return Matrix::gen_multiply_matrix<Vertex, float, Vertex, 4, 4, 4>(temp, transpose.m);
}

Vertex operator*(float x, const Vertex &vertex) {
  return { vertex.x * x, vertex.y * x, vertex.z * x, vertex.w * x };
}

}; // namespace maths
