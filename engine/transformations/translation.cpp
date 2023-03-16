#include "translation.h"

namespace transformations {

Translation::Translation(float x, float y, float z) : x(x), y(y), z(z) {
  std::cout << "Translation created\n";
  std::cout << x << ' ' << y << ' ' << z << '\n';
}

void Translation::apply() const noexcept {
  std::cout << "Translation applied\n";
  std::cout << x << ' ' << y << ' ' << z << '\n';
  glTranslatef(x, y, z);
}

} // namespace transformations
