#include "camera.h"
#include <cmath>

namespace camera_engine {

Camera::Camera(Coordinates position, Coordinates lookAt, Coordinates up,
               Pov projection)
    : position(position), lookAt(lookAt), up(up), projection(projection) {
  this->alpha = std::atan2(position.x, position.y);
  this->beta = std::atan2(position.y, position.x);
  this->radius = static_cast<float>(std::sqrt(std::pow(position.x, 2) +
                                              std::pow(position.y, 2) +
                                              std::pow(position.z, 2)));
  std::cout << "radius = " << this->radius << '\n';
  std::cout << "alpha = " << this->alpha << '\n';
  std::cout << "beta = " << this->beta << '\n';
}

void Camera::moveHorizontally(float dx) noexcept {
  if (this->currentMode == CameraMode::Explorer) {
    this->alpha += dx;
    if (this->alpha < 0)
      this->alpha = 2 * std::numbers::pi_v<float>;
    else if (this->alpha > 2 * std::numbers::pi_v<float>)
      this->alpha = 0;
  } else {
  }
}

inline void Camera::moveVertically(float dx) noexcept {
  if (this->currentMode == CameraMode::Explorer) {
    this->beta += dx;
    if (this->beta > std::numbers::pi_v<float> * (3.0f / 2.0f)) {
      this->beta = std::numbers::pi_v<float> * (3.0f / 2.0f);
    } else if (this->beta < std::numbers::pi_v<float> / 2.0f) {
      this->beta = std::numbers::pi_v<float> / 2.0f;
    } else if (this->beta < 0)
      this->beta = 2 * std::numbers::pi_v<float>;
  } else {
  }
}

} // namespace camera_engine
