#ifndef SCALE_H
#define SCALE_H

#include "transform.h"
#include <GLUT/glut.h>

namespace transformations {

class Scale : public Transform {
public:
  Scale(float, float, float);
  ~Scale() override = default;
  void apply() const noexcept override;

private:
  float x{0}, y{0}, z{0};
};

} // namespace transformations
#endif // SCALE_H
