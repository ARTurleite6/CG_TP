#ifndef FIGURE_H
#define FIGURE_H
#include "Triangle.h"
#include "my_math.h"

class Figure {
public:
  Figure() = default;
  explicit Figure(const std::vector<float> &args);
  virtual ~Figure() = default;

  virtual void storeVertices(std::string_view outFile) const noexcept;
  void computeOperation(const maths::Matrix<float, 4, 4> &m) noexcept;

  std::vector<maths::Vertex> vertices;
  std::vector<maths::Vertex> normals;
  std::vector<maths::Vertex2D> texCoords;
};

#endif // FIGURE_H
