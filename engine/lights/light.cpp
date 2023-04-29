#include "light.h"

void Light::configureColor() const noexcept {
  this->enable();

  float dark[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0 + index, GL_AMBIENT, dark);
  glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0 + index, GL_SPECULAR, white);
}
