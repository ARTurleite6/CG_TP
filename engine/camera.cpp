#include "camera.h"

namespace camera_engine {

Camera::Camera(Coordinates position, Coordinates lookAt, Coordinates up,
               Pov projection)
    : position(position), lookAt(lookAt), up(up), projection(projection) {}

} // namespace camera_engine
