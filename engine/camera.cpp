#include "camera.h"
#include <cmath>
#include <stdexcept>

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

void Camera::moveUp(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {

    std::cout << "moving_beta = "
              << (this->beta == std::numbers::pi_v<float> / 2.0f) << '\n';
    if (this->beta + 0.1f < std::numbers::pi_v<float> / 2.0f ||
        this->beta > std::numbers::pi_v<float> * (3.0f / 2.0f)) {
      this->beta += dx;
      if (this->beta > 2 * std::numbers::pi_v<float>)
        this->beta = 0;
    }
    this->position = this->getPosition();
  } else {

    auto new_position = this->getNewPosition(dx);
    this->position =
        Coordinates{new_position.x, new_position.y, new_position.z};
  }
}

void Camera::moveDown(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {

    if (this->beta - 0.1f > std::numbers::pi_v<float> * (3.0f / 2.0f) ||
        this->beta < std::numbers::pi_v<float> / 2.0f) {
      this->beta -= dx;
      if (this->beta < 0)
        this->beta = std::numbers::pi_v<float> * 2;
    }
    this->position = this->getPosition();
  } else {

      auto new_position = this->getNewPosition(-dx);
      this->position = 
        Coordinates{new_position.x, new_position.y, new_position.z};
  }
}

void Camera::moveRight(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {

    this->alpha += dx;
    if (this->alpha > 2 * std::numbers::pi_v<float>)
      this->alpha = 0.0f;
    this->position = this->getPosition();
  } else {
  }
}

void Camera::moveLeft(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {

    this->alpha -= dx;
    if (this->alpha < 0)
      this->alpha = 2 * std::numbers::pi_v<float>;
    this->position = this->getPosition();
  } else {
  }
}

[[nodiscard]] utils::Vertex Camera::getNewPosition(float dx) const noexcept {

  auto lookAt =
      utils::Vertex{this->lookAt.x, this->lookAt.y, this->lookAt.z, 1.0f};

  auto position =
      utils::Vertex{this->position.x, this->position.y, this->position.z, 1.0f};

  auto direction = lookAt - position;
  direction.normalize();

  return position + (direction * dx);
}

} // namespace camera_engine
