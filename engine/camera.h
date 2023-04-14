#ifndef CAMERA_H
#define CAMERA_H
#include "utils.h"
#include <cmath>
#include <limits>

namespace camera_engine {

enum class CameraMode { FPS, Explorer };

struct Coordinates {
  float x{}, y{}, z{};
};

struct Pov {
  float fov{}, near{}, far{};
};

class Camera {
public:
  Camera() = default;
  Camera(Coordinates position, Coordinates lookAt, Coordinates up,
         Pov projection);
  Camera(Camera &&) = default;
  Camera(const Camera &) = default;
  Camera &operator=(Camera &&) = default;
  Camera &operator=(const Camera &) = default;
  ~Camera() = default;

  [[nodiscard]] inline camera_engine::Pov getProjection() const noexcept {
    return projection;
  }

  void
  handleInput(const std::array<bool, std::numeric_limits<unsigned char>::max()>
                  &keyboard) noexcept;

  void handleMouseMotion(int x, int y) noexcept;

  [[nodiscard]] inline camera_engine::Coordinates getPosition() const noexcept {
    if (this->currentMode == CameraMode::Explorer) {
      return camera_engine::Coordinates{
          this->radius * std::sin(this->alpha) * std::cos(this->beta),
          this->radius * std::sin(this->beta),
          this->radius * std::cos(this->alpha) * std::cos(this->beta),
      };
    } else {
      return this->position;
    }
  }

  [[nodiscard]] inline camera_engine::Coordinates getLookAt() const noexcept {
    if (this->currentMode == CameraMode::Explorer)
      return lookAt;
    else {
      return Coordinates{
          this->radius * std::sin(this->alpha) * std::cos(this->beta),
          this->radius * std::sin(this->beta),
          this->radius * std::cos(this->alpha) * std::cos(this->beta),
      };
    }
  }

  [[nodiscard]] inline camera_engine::Coordinates getUp() const noexcept {
    return up;
  }

  inline void setTrackingMode(int tracking) { this->tracking = tracking; }

  inline void setMousePosition(int x, int y) noexcept {
    this->initialMouseX = x;
    this->initialMouseY = y;
  }

private:
  void updateNewPosition(float dx) noexcept;

  void moveRight(float dx);
  void moveUp(float dx);
  void moveLeft(float dx);
  void moveDown(float dx);

  inline void toggleMode() noexcept {
    this->currentMode = this->currentMode == CameraMode::FPS
                            ? CameraMode::Explorer
                            : CameraMode::FPS;
    if (this->currentMode == CameraMode::Explorer) {
      this->lookAt = Coordinates{0.0f, 0.0f, 0.0f};
      this->alpha = this->previousAlpha;
      this->beta = this->previousBeta;
    } else {
      this->previousAlpha = this->alpha;
      this->previousBeta = this->beta;
      this->beta = this->alpha = 0.0f;
    }
  }

  CameraMode currentMode{CameraMode::Explorer};
  float alpha{0.0f};
  float beta{0.0f};
  float radius{0.0f};
  bool doubleSpeed{false};
  Coordinates position{0, 0, 0};
  Coordinates lookAt{0, 0, 0};
  Coordinates up{0, 0, 0};
  Pov projection{0, 0, 0};

  float previousAlpha{0.0f}, previousBeta{0.0f};
  int initialMouseX{0}, initialMouseY{0};

  int tracking{0};
};

}; // namespace camera_engine

#endif
