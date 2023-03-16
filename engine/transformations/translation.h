#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "transform.h"
#include <GLUT/glut.h>

namespace transformations {
class Translation : public Transform {
public:
  Translation(float, float, float);
  ~Translation() override = default;
  void apply() const noexcept override;

private:
  float x{0}, y{0}, z{0};
};

}; // namespace transformations

#endif // TRANSLATION_H
