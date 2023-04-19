#ifndef SCALE_H
#define SCALE_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "transform.h"

namespace transformations {

class Scale : public Transform {
public:
  Scale(float, float, float);
  ~Scale() override = default;
  void apply(int elapsedTime) noexcept override;

  [[nodiscard]] TypeTransformation getType() const noexcept override {
    return TypeTransformation::Scale;
  }

private:
  float x{0}, y{0}, z{0};
};

} // namespace transformations
#endif // SCALE_H
