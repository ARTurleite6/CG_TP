#ifndef SPHERE_H
#define SPHERE_H
#include "figure.h"

class Sphere : public Figure {
public:
  Sphere() = default;
  explicit Sphere(const std::vector<float> &args);
  Sphere(Sphere &&) = default;
  Sphere(const Sphere &) = default;
  Sphere &operator=(Sphere &&) = default;
  Sphere &operator=(const Sphere &) = default;
  ~Sphere() override = default;

private:
  float radius{}, slices{}, stacks{};
};

#endif
