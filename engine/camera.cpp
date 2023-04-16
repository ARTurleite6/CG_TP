#include "camera.h"
#include <cmath>
#include <stdexcept>

namespace camera_engine {

Camera::Camera(utils::Vertex position, utils::Vertex lookAt, utils::Vertex up,
               Pov projection)
    : position(position), initialLookAt(lookAt), up(up), projection(projection),
      currentLookAt(lookAt) {
  this->alpha = std::atan2(position.x, position.y);
  this->alpha = this->alpha * (180 / std::numbers::pi_v<float>);
  this->beta = std::atan2(position.y, position.x);
  this->beta = this->beta * (180 / std::numbers::pi_v<float>);
  this->radius = static_cast<float>(std::sqrt(std::pow(position.x, 2) +
                                              std::pow(position.y, 2) +
                                              std::pow(position.z, 2)));
}

[[nodiscard]] utils::Vertex Camera::getPosition() const noexcept {
  if (this->currentMode == CameraMode::Explorer) {
    return this->getPolarCoordinates();
  } else {
    return this->position;
  }
}

[[nodiscard]] utils::Vertex Camera::getPolarCoordinates() const noexcept {
  auto alphaR = this->alpha * (std::numbers::pi_v<float> / 180.0f);
  auto betaR = this->beta * (std::numbers::pi_v<float> / 180.0f);

  return utils::Vertex{this->radius * std::sin(alphaR) * std::cos(betaR),
                       this->radius * std::sin(betaR),
                       this->radius * std::cos(alphaR) * std::cos(betaR), 1.0f};
}

void Camera::handleInput(
    const std::array<bool, std::numeric_limits<unsigned char>::max()>
        &keyboard) noexcept {

  auto speedToUse = 5.0f;
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

  if (keyboard['m'])
    this->toggleMode();
}

void Camera::moveUp(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {
    this->radius -= dx * 0.01f;
    if (this->radius < 0)
      this->radius = 0;
  } else {
    this->updateNewPosition(dx * 0.1f);
  }
}

void Camera::moveDown(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {
    this->radius += dx * 0.01f;
  } else {
    this->updateNewPosition(-dx * 0.1f);
  }
}

void Camera::moveRight(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {
    this->alpha += dx;
  } else {

    auto direction = this->currentLookAt - position;
    direction.normalize();

    this->up.normalize();

    auto vector = direction.crossProduct(up);

    this->position += vector;
    this->currentLookAt += vector;
  }
}

void Camera::moveLeft(float dx) {
  if (dx < 0)
    throw std::invalid_argument("dx must be greater than zero");

  if (this->currentMode == CameraMode::Explorer) {
    this->alpha -= dx;
  } else {

    auto direction = this->currentLookAt - this->position;
    direction.normalize();

    up.normalize();

    auto vector = up.crossProduct(direction);

    this->position += vector * dx;

    this->currentLookAt += vector * dx;
  }
}

void Camera::updateNewPosition(float dx) noexcept {

  auto direction = this->currentLookAt - position;
  direction.normalize();

  this->position += (direction * dx);
  this->currentLookAt += (direction * dx);
}

void Camera::handleMouseMotion(int x, int y) noexcept {

  if (tracking == 0)
    return;

  int deltaX = (x - this->initialMouseX);
  int deltaY = (y - this->initialMouseY);

  std::cout << "deltaX = " << deltaX << ", deltaY = " << deltaY << '\n';

  float alphaAux = this->alpha + static_cast<float>(deltaX);
  float betaAux = this->beta + static_cast<float>(deltaY);

  if (betaAux > 85.0f) {
    betaAux = 85.0f;
  }

  this->alpha = alphaAux;
  this->beta = betaAux;

  this->setMousePosition(x, y);

  if (this->currentMode == CameraMode::FPS) {
    this->currentLookAt = {
        this->position.x +
            this->radius * std::sin(this->alpha) * std::cos(this->beta),
        this->position.y + this->radius * std::sin(this->beta),
        this->position.z +
            this->radius * std::cos(this->alpha) * std::cos(this->beta),
        1.0f};
  }
} // namespace camera_engine

[[nodiscard]] utils::Vertex Camera::getLookAt() const noexcept {
  if (this->currentMode == CameraMode::Explorer)
    return this->initialLookAt;
  else {
    return this->currentLookAt;
  }
}

void Camera::toggleMode() noexcept {
  if (this->currentMode == CameraMode::Explorer) {
    this->currentLookAt = this->initialLookAt;
    this->position = this->getPolarCoordinates();
    this->currentMode = CameraMode::FPS;
  } else {
    this->currentMode = CameraMode::Explorer;
  }
  this->beta = -this->beta;
  this->alpha = -this->alpha;
}

} // namespace camera_engine
