#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>

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

  [[nodiscard]] inline camera_engine::Coordinates getPosition() const noexcept {
    return camera_engine::Coordinates{
        this->radius * std::sin(this->alpha) * std::cos(this->beta),
        this->radius * std::sin(this->beta),
        this->radius * std::cos(this->alpha) * std::cos(this->beta),
    };
    // return position;
  }

  [[nodiscard]] inline camera_engine::Coordinates getLookAt() const noexcept {
    return lookAt;
  }

  [[nodiscard]] inline camera_engine::Coordinates getUp() const noexcept {
    return up;
  }

  void moveHorizontally(float dx) noexcept;

  void moveVertically(float dx) noexcept;

private:
  CameraMode currentMode{CameraMode::Explorer};
  float alpha{0.0f};
  float beta{0.0f};
  float radius{0.0f};
  Coordinates position{0, 0, 0};
  Coordinates lookAt{0, 0, 0};
  Coordinates up{0, 0, 0};
  Pov projection{0, 0, 0};
};

}; // namespace camera_engine

#endif
