#ifndef FIGURE_H
#define FIGURE_H
#include "Triangle.h"

class Figure {
public:
    Figure() = default;
  explicit Figure(const std::vector<float> &args);
  virtual ~Figure() = default;

  void storeVertices(std::string_view outFile) const noexcept;
  void computeOperation(const Matrix &m) noexcept;

  std::vector<Triangle> triangles;
};

#endif // FIGURE_H
