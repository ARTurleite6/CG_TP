#ifndef ROTATION_H
#define ROTATION_H
#include "tinyxml2.h"
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
  explicit Rotation(const tinyxml2::XMLElement *rotation);
  ~Rotation() override = default;
  void apply(int elapsedTime) noexcept override;

  [[nodiscard]] TypeTransformation getType() const noexcept override {
    return TypeTransformation::Rotate;
  }

private:
  float angle{0}, x{0}, y{0}, z{0};
  float time{0.0f};
  bool timedRotation{false};
};
} // namespace transformations
#endif //  ROTATION_H
