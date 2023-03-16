#ifndef ROTATION_H
#define ROTATION_H

#include "transform.h"
#include <GLUT/glut.h>
namespace transformations {
class Rotation : public Transform {
public:
  Rotation(float, float, float, float);
  ~Rotation() override = default;
  void apply() const noexcept override;

private:
  float angle{0}, x{0}, y{0}, z{0};
};
} // namespace transformations
#endif //  ROTATION_H
