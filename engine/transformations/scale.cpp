#include "scale.h"

namespace transformations {

Scale::Scale(float x, float y, float z) : x{x}, y{y}, z{z} {}

void Scale::apply(int elapsedTime) noexcept { glScalef(x, y, z); }

} // namespace transformations
