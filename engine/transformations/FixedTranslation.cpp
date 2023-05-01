#include "FixedTranslation.h"

namespace transformations {
FixedTranslation::FixedTranslation(const tinyxml2::XMLElement *translation)
    : x(queryFloatAttr(translation, "x")), y(queryFloatAttr(translation, "y")),
      z(queryFloatAttr(translation, "z")) {}

void FixedTranslation::apply(int elapsedTime) noexcept {
  glTranslatef(this->x, this->y, this->z);
}
} // namespace transformations
