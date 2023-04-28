#ifndef BEZZIER_H
#define BEZZIER_H

#include "figure.h"
#include "io.h"
#include "my_math.h"
class Bezzier : public Figure {

public:
  Bezzier(const std::string &filepath, float tesselation);

  void storeVertices(std::string_view outFile) const noexcept override;

private:
  static std::pair<maths::Vertex, maths::Vertex>
  getPoint(const maths::Matrix<Vertex, 4, 4> &mA, float u, float v);

  [[nodiscard]] std::pair<std::vector<maths::Vertex>,
                          std::vector<maths::Vertex>>
  calculatePoints() const noexcept;
  float tesselation{0.0f};
  std::vector<std::array<int, 16>> patchesIndices{};
};

#endif // BEZZIER_H
