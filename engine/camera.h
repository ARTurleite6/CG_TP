#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>

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

private:
  Coordinates position{0, 0, 0};
  Coordinates lookAt{0, 0, 0};
  Coordinates up{0, 0, 0};
  Pov projection{0, 0, 0};
};

}; // namespace camera_engine

#endif
