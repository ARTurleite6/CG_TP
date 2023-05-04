#ifndef CAMERA_H
#define CAMERA_H
#include "include.h"
#include "my_math.h"

namespace camera_engine {

using namespace maths;

enum class CameraMode { FPS, Explorer };

struct Pov {
  float fov{}, near{}, far{};
};

class Camera {
public:
  Camera() = default;
  Camera(Vertex position, Vertex lookAt, Vertex up, Pov projection,
         std::uint32_t window_width, std::uint32_t window_height);
  Camera(Camera &&) = default;
  Camera(const Camera &) = default;
  Camera &operator=(Camera &&) = default;
  Camera &operator=(const Camera &) = default;
  ~Camera() = default;

  void place() noexcept;

  void
  handleInput(const std::array<bool, std::numeric_limits<unsigned char>::max()>
                  &keyboard) noexcept;

  void handleMouseMotion(int x, int y) noexcept;

  inline void setTrackingMode(int tracking) { this->tracking = tracking; }

  inline void setMousePosition(int x, int y) noexcept {
    this->initialMouseX = x;
    this->initialMouseY = y;
  }

  void setPerspective(float ratio) const noexcept;

  void toggleMode() noexcept;

private:
  void updateNewPosition(float dx) noexcept;

  [[nodiscard]] Vertex getPosition() const noexcept;

  [[nodiscard]] Vertex getLookAt() const noexcept;

  [[nodiscard]] inline Vertex getUp() const noexcept { return up; }

  void moveRight(float dx);
  void moveUp(float dx);
  void moveLeft(float dx);
  void moveDown(float dx);

  [[nodiscard]] Vertex getPolarCoordinates() const noexcept;

  [[nodiscard]] inline camera_engine::Pov getProjection() const noexcept {
    return projection;
  }

  CameraMode currentMode{CameraMode::Explorer};
  float alpha{0.0f};
  float beta{0.0f};
  float radius{0.0f};
  bool doubleSpeed{false};
  Vertex position{0, 0, 0, 1.0f};
  Vertex initialLookAt{0, 0, 0, 1.0f};
  Vertex currentLookAt{0, 0, 0, 1.0f};
  Vertex up{0, 0, 0, 0.0f};
  Pov projection{0, 0, 0};

  int initialMouseX{0}, initialMouseY{0};

  std::uint32_t window_width{800}, window_height{600};

  int tracking{0};
};

}; // namespace camera_engine

#endif
