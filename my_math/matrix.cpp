#include "matrix.h"
#include "my_math.h"

namespace matrix {

template <> Matrix<maths::Vertex, 4, 4> Matrix<maths::Vertex, 4, 4>::patchBezzier() const noexcept {
  auto m = Matrix<float, 4, 4>{-1.0f, +3.0f, -3.0f, +1.0f, +3.0f, -6.0f,
                               +3.0f, +0.0f, -3.0f, +3.0f, +0.0f, +0.0f,
                               +1.0f, +0.0f, +0.0f, +0.0f};

  auto transpose = m.transpose();
  auto temp = *this * m;

  return m * *this * transpose;
}

Matrix<float, 4, 4> translate(const Matrix<float, 4, 4> &m, const maths::Vertex &v) noexcept {
  Matrix result = m;

  result[0][3] = v.x;
  result[1][3] = v.y;
  result[2][3] = v.z;

  return result;
}

Matrix<float, 4, 4> scale(const Matrix<float, 4, 4> &m, const maths::Vertex &v) noexcept {
  Matrix result = m;

  result[0][0] = v.x;
  result[1][1] = v.y;
  result[2][2] = v.z;

  return result;
}

Matrix<float, 4, 4> rotate(const Matrix<float, 4, 4> &m, const maths::Vertex &v, float angle) noexcept {

  Matrix result = m;

  if (v.x != 0.0f) {
    result[1][1] = std::cos(angle);
    result[1][2] = -std::sin(angle);
    result[2][1] = std::sin(angle);
    result[2][2] = std::cos(angle);
  } else if (v.y != 0.0f) {
    result[0][0] = std::cos(angle);
    result[0][2] = std::sin(angle);
    result[2][0] = -std::sin(angle);
    result[2][2] = std::cos(angle);
  } else if (v.z != 0.0f) {
    result[0][0] = std::cos(angle);
    result[0][1] = -std::sin(angle);
    result[1][0] = std::sin(angle);
    result[1][1] = std::cos(angle);
  }

  return result;
}


}; // namespace matrix