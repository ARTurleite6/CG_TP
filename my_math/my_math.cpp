#include "my_math.h"

namespace maths {

std::ostream &operator<<(std::ostream &oos, const Vertex2D &vertex) {
  return oos << vertex.x << ' ' << vertex.y;
}

Vertex2D::Vertex2D(float x, float y) : x(x), y(y) {}

Vertex::Vertex(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

float Vertex::size() const noexcept {
  return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z +
                   this->w * this->w);
}

void Vertex::operator*=(const Matrix<float, 4, 4> &m) noexcept {
  const Vertex v = *this;

  this->x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
  this->y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
  this->z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
  this->w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
}

Vertex &Vertex::operator*(const Matrix<float, 4, 4> &m) noexcept {

  const Vertex v = *this;

  this->x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
  this->y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
  this->z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
  this->w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

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
  return {v.x * constant, v.y * constant, v.z * constant, v.w * constant};
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

float Vertex::operator*(const Vertex &vertex) const noexcept {
  return this->x * vertex.x + this->y * vertex.y + this->z * vertex.z +
         this->w * vertex.w;
}

Vertex operator*(float x, const Vertex &vertex) {
  return {vertex.x * x, vertex.y * x, vertex.z * x, vertex.w * x};
}

std::ostream &operator<<(std::ostream &oos, const Vertex &v) {
  return oos << "Vertex ( x = " << v.x << ", y = " << v.y << ", z = " << v.z
             << ", w = " << v.w << ");";
}

template <>
Matrix<Vertex, 4, 4> Matrix<Vertex, 4, 4>::patchBezzier() const noexcept {
  auto m = Matrix<float, 4, 4>{-1.0f, +3.0f, -3.0f, +1.0f, +3.0f, -6.0f,
                               +3.0f, +0.0f, -3.0f, +3.0f, +0.0f, +0.0f,
                               +1.0f, +0.0f, +0.0f, +0.0f};

  auto transpose = m.transpose();
  auto temp = *this * m;

  return m * *this * transpose;
}

Matrix<float, 4, 4> translate(const Matrix<float, 4, 4> &m,
                              const maths::Vertex &v) noexcept {
  Matrix result = m;

  result[0][3] = v.x;
  result[1][3] = v.y;
  result[2][3] = v.z;

  return result;
}

Matrix<float, 4, 4> scale(const Matrix<float, 4, 4> &m,
                          const maths::Vertex &v) noexcept {
  Matrix result = m;

  result[0][0] = v.x;
  result[1][1] = v.y;
  result[2][2] = v.z;

  return result;
}

Matrix<float, 4, 4> rotate(const Matrix<float, 4, 4> &m, const maths::Vertex &v,
                           float angle) noexcept {

  const auto radians_angle = angle * (std::numbers::pi_v<float> / 180.0f);

  Matrix result = Matrix(1.0f);

  if (v.x != 0.0f) {
    result[1][1] = std::cos(radians_angle);
    result[1][2] = -std::sin(radians_angle);
    result[2][1] = std::sin(radians_angle);
    result[2][2] = std::cos(radians_angle);
  } else if (v.y != 0.0f) {
    result[0][0] = std::cos(radians_angle);
    result[0][2] = std::sin(radians_angle);
    result[2][0] = -std::sin(radians_angle);
    result[2][2] = std::cos(radians_angle);
  } else if (v.z != 0.0f) {
    result[0][0] = std::cos(radians_angle);
    result[0][1] = -std::sin(radians_angle);
    result[1][0] = std::sin(radians_angle);
    result[1][1] = std::cos(radians_angle);
  }

  return m * result;
}

template <>
Vertex Matrix<float, 4, 4>::operator*(const Vertex &v) const noexcept {
  return Vertex{
      this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z +
          this->m[0][3] * v.w,
      this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z +
          this->m[1][3] * v.w,
      this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z +
          this->m[2][3] * v.w,
      this->m[3][0] * v.x + this->m[3][1] * v.y + this->m[3][2] * v.z +
          this->m[3][3] * v.w,
  };
}

}; // namespace maths
