#include "translation.h"

namespace transformations {

Translation::Translation(float x, float y, float z) : x(x), y(y), z(z) {
}

void Translation::apply() const noexcept {
  glTranslatef(x, y, z);
}

} // namespace transformations
