#ifndef MY_MATH_H
#define MY_MATH_H
#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace maths {

float withinRange(float value, float min, float max);

template <class T = float, std::uint32_t L = 4, std::uint32_t C = 4>
class Matrix;

class Vertex2D {

public:
  Vertex2D(float x, float y);
  ~Vertex2D() = default;

  friend std::ostream &operator<<(std::ostream &oos, const Vertex2D &vertex);

  [[nodiscard]] inline float getX() const noexcept { return x; }
  [[nodiscard]] inline float getY() const noexcept { return y; }

  inline void setX(float x) noexcept { this->x = x; }
  inline void setY(float y) noexcept { this->y = y; }

private:
  float x, y;
};

struct Vertex {
  Vertex() = default;
  Vertex(float x, float y, float z, float w);
  Vertex(Vertex &&) = default;
  Vertex(const Vertex &) = default;
  Vertex &operator=(Vertex &&) = default;
  Vertex &operator=(const Vertex &) = default;
  Vertex &operator*(const Matrix<float, 4, 4> &m) noexcept;
  void operator*=(const Matrix<float, 4, 4> &m) noexcept;
  Vertex operator+(const Vertex &m) const noexcept;
  Vertex operator-(const Vertex &) const noexcept;
  friend Vertex operator*(const Vertex &v, float constant) noexcept;
  Vertex &operator+=(const Vertex &) noexcept;
  float operator*(const Vertex &) const noexcept;
  friend std::ostream &operator<<(std::ostream &oos, const Vertex &v);

  static Vertex fromSpherical(float radius, float alpha, float beta);

  [[nodiscard]] Vertex crossProduct(const Vertex &) const noexcept;
  ~Vertex() = default;
  void normalize() noexcept;
  [[nodiscard]] float size() const noexcept;

  float x{}, y{}, z{}, w{};
};

Vertex operator*(float x, const Vertex &vertex);
std::ostream &operator<<(std::ostream &oos, const Vertex &v);

template <class T, std::uint32_t L, std::uint32_t C> class Matrix {
public:
  Matrix() = default;
  explicit Matrix(const T &value) {
    std::uint32_t column = 0;
    for (int i = 0; i < L; ++i) {
      this->m[i][column] = value;
      column += 1;
    }
  }

  explicit Matrix(const std::array<std::array<T, C>, L> &arr) {
    for (int i = 0; i < L; ++i) {
      for (int j = 0; j < C; ++j) {
        this->m[i][j] = arr[i][j];
      }
    }
  }

  Matrix(std::initializer_list<T> values) {
    if (values.size() != L * C) {
      throw std::invalid_argument("Invalid number of arguments");
    }

    std::uint32_t i = 0;

    for (const auto &value : values) {
      const auto line = i / C;
      this->m[line][i % C] = value;
      ++i;
    }
  }

  template <class Second, std::uint32_t CS>
  friend Matrix<decltype(T() * Second()), L, CS>
  operator*(const Matrix<T, L, C> &first, const Matrix<Second, C, CS> &second) {
    Matrix<decltype(T() * Second()), L, CS> res{};
    for (int i = 0; i < L; ++i) {
      for (int j = 0; j < CS; ++j) {
        for (int w = 0; w < C; ++w) {
          res[i][j] += first.m[i][w] * second[w][j];
        }
      }
    }
    return res;
  }

  template <class Second, class R, std::uint32_t CS>
  Matrix<R, L, CS> &operator*(const Matrix<Second, C, CS> &other) {
    for (int i = 0; i < L; ++i) {
      for (int j = 0; j < CS; ++j) {
        for (int w = 0; w < C; ++w) {
          this->m[i][j] += this->m[i][w] * other.m[w][j];
        }
      }
    }

    return *this;
  }

  Vertex operator*(const Vertex &v) const noexcept;

  const std::array<T, C> &operator[](int i) const {
    if (this->m.size() <= i)
      throw std::out_of_range("Matrix out of bounds");
    return this->m[i];
  }

  std::array<T, C> &operator[](int i) {
    if (this->m.size() <= i)
      throw std::out_of_range("Matrix out of bounds");
    return this->m[i];
  }

  Matrix transpose() const noexcept {
    Matrix new_matrix;

    for (int i = 0; i < L; ++i) {
      for (int j = 0; j < C; ++j) {
        new_matrix.m[i][j] = this->m[j][i];
      }
    }

    return new_matrix;
  }

  [[nodiscard]] Matrix<maths::Vertex, 4, 4> patchBezzier() const noexcept;

private:
  std::array<std::array<T, C>, L> m{};
};

Matrix<float, 4, 4> translate(const Matrix<float, 4, 4> &m,
                              const maths::Vertex &v) noexcept;
Matrix<float, 4, 4> scale(const Matrix<float, 4, 4> &m,
                          const maths::Vertex &v) noexcept;
Matrix<float, 4, 4> rotate(const Matrix<float, 4, 4> &m, const maths::Vertex &v,
                           float angle) noexcept;

}; // namespace maths

// template <> std::is_swappable_v<utils::Vertex>{
// };

#endif
