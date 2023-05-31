#include "light.h"

std::uint32_t Light::current_index = 0;

std::uint32_t Light::getNextIndex() {
  if (Light::current_index > 7) {
    throw std::invalid_argument("Max number of lights exceeded");
  }

  return Light::current_index++;
}

void Light::configureColor() const noexcept {
  this->enable();

  float dark[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0 + index, GL_AMBIENT, dark);
  glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0 + index, GL_SPECULAR, white);
}
