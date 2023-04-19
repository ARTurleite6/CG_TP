#include "rotation.h"
#include "tinyxml2.h"

namespace transformations {

Rotation::Rotation(float angle, float x, float y, float z)
    : angle{angle}, x{x}, y{y}, z{z} {}

Rotation::Rotation(const tinyxml2::XMLElement *rotation) {
  const auto time = rotation->FindAttribute("time");
  if (time != nullptr) {
    this->time = time->FloatValue();
    this->timedRotation = true;
  } else {
    rotation->QueryAttribute("angle", &this->angle);
    this->time = 0.0f;
    this->timedRotation = false;
  }
  rotation->QueryAttribute("x", &this->x);
  rotation->QueryAttribute("y", &this->y);
  rotation->QueryAttribute("z", &this->z);
}

// 10 segundos -> 360 angle
// x segundos -> y angle
//
// y = (x * 360) / x;

void Rotation::apply(int elapsedTime) noexcept {
  float angleToUse = this->angle;
  if (this->timedRotation) {
    auto seconds = static_cast<float>(elapsedTime) / 1000.0f;
    angleToUse = (seconds * 360) / this->time;
  }
  glRotatef(angleToUse, x, y, z);
}

} // namespace transformations
