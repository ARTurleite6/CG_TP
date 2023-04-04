#ifndef CUBE_H
#define CUBE_H
#include "figure.h"
#include "Plane.h"

class Box : public Figure {
public:
  Box() = default;
  explicit Box(const std::vector<float> &args) noexcept;
  Box(Box &&) = default;
  Box(const Box &) = default;
  Box &operator=(Box &&) = default;
  Box &operator=(const Box &) = default;
  ~Box() override = default;

private:
  float dimensions{}, divisions{};
};

#endif // CUBE_H
