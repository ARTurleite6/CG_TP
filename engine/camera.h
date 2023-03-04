#ifndef CAMERA_H
#define CAMERA_H

namespace camera_engine {

struct Coordinates {
  std::uint32_t x{}, y{}, z{};
};

struct Pov {
  std::uint32_t fov{}, near{}, far{};
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
    return position;
  }

  [[nodiscard]] inline camera_engine::Coordinates getLookAt() const noexcept {
    return lookAt;
  }

  [[nodiscard]] inline camera_engine::Coordinates getUp() const noexcept {
    return up;
  }

private:
  Coordinates position{0, 0, 0};
  Coordinates lookAt{0, 0, 0};
  Coordinates up{0, 0, 0};
  Pov projection{0, 0, 0};
};

}; // namespace camera_engine

#endif
