#ifndef ROTATION_H
#define ROTATION_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "transform.h"
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
