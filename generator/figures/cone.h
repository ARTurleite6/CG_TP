#ifndef CONE_H
#define CONE_H

#include "figure.h"

class Cone : public Figure {
public:
  Cone() = default;
  explicit Cone(const std::vector<float> &data);
  Cone(Cone &&) = default;
  Cone(const Cone &) = default;
  Cone &operator=(Cone &&) = default;
  Cone &operator=(const Cone &) = default;
  ~Cone() override = default;

private:
  float radius{}, height{}, slices{}, stacks{};
};

#endif // CONE_H
