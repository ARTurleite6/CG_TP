#include "camera.h"
#include <GL/glu.h>

namespace camera_engine {

Camera::Camera(Vertex position, Vertex lookAt, Vertex up, Pov projection,
               std::uint32_t window_width, std::uint32_t window_height)
    : position(position), initialLookAt(lookAt), up(up), projection(projection),
      currentLookAt(lookAt), window_width(window_width),
      window_height(window_height) {
  this->alpha = std::atan2(position.x, position.y);
  this->alpha = this->alpha * (180 / std::numbers::pi_v<float>);
  this->beta = std::atan2(position.y, position.x);
  this->beta = this->beta * (180 / std::numbers::pi_v<float>);
  this->radius = static_cast<float>(std::sqrt(std::pow(position.x, 2) +
                                              std::pow(position.y, 2) +
                                              std::pow(position.z, 2)));
}

[[nodiscard]] Vertex Camera::getPosition() const noexcept {
  if (this->currentMode == CameraMode::Explorer) {
    return this->getPolarCoordinates();
  } else {
    return this->position;
  }
}

[[nodiscard]] Vertex Camera::getPolarCoordinates() const noexcept {
  auto alphaR = this->alpha * (std::numbers::pi_v<float> / 180.0f);
  auto betaR = this->beta * (std::numbers::pi_v<float> / 180.0f);

  return Vertex::fromSpherical(this->radius, alphaR, betaR);
}

void Camera::handleInput(
    const std::array<bool, std::numeric_limits<unsigned char>::max()>
        &keyboard) noexcept {

  auto speedToUse = 1.0f;
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

  if (tracking == 0 && this->currentMode == CameraMode::Explorer)
    return;

  int deltaX = (this->initialMouseX - x);
  int deltaY = (this->initialMouseY - y);

  float sensivity = (this->currentMode == CameraMode::FPS) ? 0.001f : 1.0f;

  float alphaAux = this->alpha + static_cast<float>(deltaX) * sensivity;
  float betaAux = this->beta + static_cast<float>(deltaY) * sensivity;

  if (betaAux > 85.0f) {
    betaAux = 85.0f;
  } else if (betaAux < -85.0f) {
    betaAux = -85.0f;
  }

  this->alpha = alphaAux;
  this->beta = betaAux;

  if (this->currentMode == CameraMode::Explorer)
    this->setMousePosition(x, y);
  else {
    auto position = this->getPosition();

    this->currentLookAt =
        position + Vertex::fromSpherical(this->radius, this->alpha, this->beta);
  }

} // namespace camera_engine

[[nodiscard]] Vertex Camera::getLookAt() const noexcept {
  if (this->currentMode == CameraMode::Explorer)
    return this->initialLookAt;
  else {
    return this->currentLookAt;
  }
}

void Camera::toggleMode() noexcept {
  if (this->currentMode == CameraMode::Explorer) {
    glutSetCursor(GLUT_CURSOR_NONE);
    this->currentLookAt = this->initialLookAt;
    this->position = this->getPolarCoordinates();
    this->currentMode = CameraMode::FPS;
  } else {
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    this->currentMode = CameraMode::Explorer;
  }
  this->beta = -this->beta;
  this->alpha = -this->alpha;
}

void Camera::place() noexcept {

  if (this->currentMode == CameraMode::FPS) {
    glutWarpPointer(static_cast<int>(this->window_width / 2),
                    static_cast<int>(this->window_height / 2));
    this->setMousePosition(static_cast<int>(this->window_width / 2),
                           static_cast<int>(this->window_height / 2));
  }
  auto lookAt = this->getLookAt();
  auto position = this->getPosition();
  gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z,
            up.x, up.y, up.z);
}

void Camera::setPerspective(float ratio) const noexcept {
  gluPerspective(this->projection.fov, ratio, this->projection.near,
                 this->projection.far);
}

} // namespace camera_engine
