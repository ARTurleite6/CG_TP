#include "rotation.h"

namespace transformations {

Rotation::Rotation(float angle, float x, float y, float z)
    : angle{angle}, x{x}, y{y}, z{z} {
}

void Rotation::apply() const noexcept { glRotatef(angle, x, y, z); }

} // namespace transformations
