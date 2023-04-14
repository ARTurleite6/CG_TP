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
}

void Camera::handleInput(
    const std::array<bool, std::numeric_limits<unsigned char>::max()>
        &keyboard) noexcept {

  auto speedToUse = 0.1f;
  if (keyboard['f'])
    this->doubleSpeed = (this->doubleSpeed == true) ? false : true;

  if (this->doubleSpeed)
    speedToUse *= 2;

  if (keyboard['w'])
    this->moveUp(speedToUse);
  if (keyboard['s'])
    this->moveDown(speedToUse);
  if (keyboard['d'])
    this->moveRight(speedToUse);
  if (keyboard['a'])
    this->moveLeft(speedToUse);

  if (keyboard['+']) {
    this->radius -= 1.0f;
    if (this->radius < 0)
      this->radius = 0.0f;
  }

  if (keyboard['-'])
    this->radius += 1.0f;

  if (keyboard['m'])
    this->toggleMode();
}

void Camera::moveUp(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {

    if (this->beta + 0.1f < std::numbers::pi_v<float> / 2.0f ||
        this->beta > std::numbers::pi_v<float> * (3.0f / 2.0f)) {
      this->beta += dx;
      if (this->beta > 2 * std::numbers::pi_v<float>)
        this->beta = 0;
    }
    this->position = this->getPosition();
  } else {
    this->updateNewPosition(dx);
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
    this->updateNewPosition(-dx);
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

    auto lookAt =
        utils::Vertex{this->lookAt.x, this->lookAt.y, this->lookAt.z, 1.0f};

    auto position = utils::Vertex{this->position.x, this->position.y,
                                  this->position.z, 1.0f};

    auto direction = lookAt - position;
    direction.normalize();

    auto up = utils::Vertex{this->up.x, this->up.y, this->up.z, 0.0f};
    up.normalize();

    auto vector = direction.crossProduct(up);

    this->position = Coordinates{
        position.x + vector.x * dx,
        position.y + vector.y * dx,
        position.z + vector.z * dx,
    };

    this->lookAt = Coordinates{
        lookAt.x + vector.x * dx,
        lookAt.y + vector.y * dx,
        lookAt.z + vector.z * dx,
    };
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
    auto lookAt =
        utils::Vertex{this->lookAt.x, this->lookAt.y, this->lookAt.z, 1.0f};

    auto position = utils::Vertex{this->position.x, this->position.y,
                                  this->position.z, 1.0f};

    auto direction = lookAt - position;
    direction.normalize();

    auto up = utils::Vertex{this->up.x, this->up.y, this->up.z, 0.0f};
    up.normalize();

    auto vector = up.crossProduct(direction);

    this->position = Coordinates{
        position.x + vector.x * dx,
        position.y + vector.y * dx,
        position.z + vector.z * dx,
    };

    this->lookAt = Coordinates{
        lookAt.x + vector.x * dx,
        lookAt.y + vector.y * dx,
        lookAt.z + vector.z * dx,
    };
  }
}

void Camera::updateNewPosition(float dx) noexcept {

  auto lookAt =
      utils::Vertex{this->lookAt.x, this->lookAt.y, this->lookAt.z, 1.0f};

  auto position =
      utils::Vertex{this->position.x, this->position.y, this->position.z, 1.0f};

  auto direction = lookAt - position;
  direction.normalize();

  auto new_position = position + (direction * dx);
  this->position = Coordinates{new_position.x, new_position.y, new_position.z};
  auto new_lookat = lookAt + (direction * dx);
  this->lookAt = Coordinates{new_lookat.x, new_lookat.y, new_lookat.z};
}

void Camera::handleMouseMotion(int x, int y) noexcept {

  if (tracking == 0 || this->currentMode == CameraMode::Explorer)
    return;

  const auto deltaX = static_cast<float>(x - this->initialMouseX) *
                      (std::numbers::pi_v<float> / 180.0f);
  const auto deltaY = static_cast<float>(y - this->initialMouseY) *
                      (std::numbers::pi_v<float> / 180.0f);

  std::cout << "Deltas: \n";
  std::cout << "deltaX = " << deltaX << '\n';
  std::cout << "deltaY = " << deltaY << '\n';

  float alphaAux = this->alpha + deltaX;
  float betaAux = this->beta + deltaY;
  if (betaAux > (std::numbers::pi_v<float> / 2.0f) - 0.2f)
    betaAux = (std::numbers::pi_v<float> / 2.0f) - 0.2f;
  else if (betaAux < -((std::numbers::pi_v<float> / 2.0f) - 0.2f)) {
    betaAux = -((std::numbers::pi_v<float> / 2.0f) - 0.2f);
  }

  if (alphaAux < 0)
    alphaAux = std::numbers::pi_v<float> * 2;

  if (alphaAux > std::numbers::pi_v<float> * 2) {
    alphaAux = 0;
  }

  std::cout << "Previous: \n";
  std::cout << "Alpha = " << this->alpha << '\n';
  std::cout << "Beta = " << this->beta << '\n';
  this->alpha = alphaAux;
  this->beta = betaAux;
  std::cout << "Current: \n";
  std::cout << "Alpha = " << this->alpha << '\n';
  std::cout << "Beta = " << this->beta << '\n';
  std::cout << "Changed angles\n";
}

} // namespace camera_engine
