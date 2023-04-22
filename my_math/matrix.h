#include "my_math.h"
#include <initializer_list>
#include <stdexcept>
#ifndef MATRIX_H
#define MATRIX_H

namespace matrix {
template <class T, std::uint32_t L, std::uint32_t C> class Matrix {
public:
  Matrix() = default;
  explicit Matrix(const T &value) {
    std::uint32_t column = 0;
    for (int i = 0; i < L; ++i) {
      this->m[column] = value;
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

    for(const auto &value : values) {
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

Matrix<float, 4, 4> translate(const Matrix<float, 4, 4> &m, const maths::Vertex &v) noexcept;
Matrix<float, 4, 4> scale(const Matrix<float, 4, 4> &m, const maths::Vertex &v) noexcept;
Matrix<float, 4, 4> rotate(const Matrix<float, 4, 4> &m, const maths::Vertex &v, float angle) noexcept;

}; // namespace matrix

#endif // MATRIX_H