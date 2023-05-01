#ifndef ROTATION_H
#define ROTATION_H
#include "../include.h"
#include "tinyxml2.h"

#include "transform.h"
namespace transformations {
class Rotation : public Transform {
public:
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
