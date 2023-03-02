#ifndef FIGURE_H
#define FIGURE_H
#include "Triangle.h"
#include <vector>
#include <string_view>

class Figure {
public:
  Figure() = default;
  explicit Figure(const std::vector<float> &args);
  Figure(Figure &&) = default;
  Figure(const Figure &) = default;
  Figure &operator=(Figure &&) = default;
  Figure &operator=(const Figure &) = default;
  virtual ~Figure() = default;

  void storeVertices(std::string_view outFile) const noexcept;
  void computeOperation(const Matrix &m) noexcept;

  std::vector<Triangle> triangles;
};

#endif // FIGURE_H
