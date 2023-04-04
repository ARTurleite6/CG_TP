#ifndef TRANSLATION_H
#define TRANSLATION_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "transform.h"

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
