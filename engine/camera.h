#ifndef CAMERA_H
#define CAMERA_H
#include "utils.h"
#include <cmath>
#include <limits>

namespace camera_engine {

enum class CameraMode { FPS, Explorer };

struct Pov {
  float fov{}, near{}, far{};
};

class Camera {
public:
  Camera() = default;
  Camera(utils::Vertex position, utils::Vertex lookAt, utils::Vertex up,
         Pov projection);
  Camera(Camera &&) = default;
  Camera(const Camera &) = default;
  Camera &operator=(Camera &&) = default;
  Camera &operator=(const Camera &) = default;
  ~Camera() = default;

  [[nodiscard]] utils::Vertex getPolarCoordinates() const noexcept;

  [[nodiscard]] inline camera_engine::Pov getProjection() const noexcept {
    return projection;
  }

  void
  handleInput(const std::array<bool, std::numeric_limits<unsigned char>::max()>
                  &keyboard) noexcept;

  void handleMouseMotion(int x, int y) noexcept;

  [[nodiscard]] utils::Vertex getPosition() const noexcept;

  [[nodiscard]] utils::Vertex getLookAt() const noexcept;

  [[nodiscard]] inline utils::Vertex getUp() const noexcept { return up; }

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

  void toggleMode() noexcept;

  CameraMode currentMode{CameraMode::Explorer};
  float alpha{0.0f};
  float beta{0.0f};
  float radius{0.0f};
  bool doubleSpeed{false};
  utils::Vertex position{0, 0, 0, 1.0f};
  utils::Vertex initialLookAt{0, 0, 0, 1.0f};
  utils::Vertex currentLookAt{0, 0, 0, 1.0f};
  utils::Vertex up{0, 0, 0, 0.0f};
  Pov projection{0, 0, 0};

  int initialMouseX{0}, initialMouseY{0};

  int tracking{0};
};

}; // namespace camera_engine

#endif
