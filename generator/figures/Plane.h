#ifndef PLANE_H
#define PLANE_H
#include "Triangle.h"
#include "figure.h"
#include "my_math.h"

class Plane : public Figure {
public:
  Plane() = default;
  explicit Plane(const std::vector<float> &args);
  Plane(Plane &&) = default;
  Plane(const Plane &) = default;
  Plane &operator=(Plane &&) = default;
  Plane &operator=(const Plane &) = default;
  ~Plane() override = default;

private:
  float dimension{}, divisions{};
};

#endif
