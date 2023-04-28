#include "pointlight.h"

PointLight::PointLight(tinyxml2::XMLElement *element, std::uint32_t index)
    : index(index) {

  this->position.x = element->FloatAttribute("posX", 0);
  this->position.y = element->FloatAttribute("posY", 0);
  this->position.z = element->FloatAttribute("posZ", 0);
  this->position.w = 1.0f;

  this->enable();
  float dark[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};

  glLightfv(GL_LIGHT0 + index, GL_AMBIENT, dark);
  glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0 + index, GL_SPECULAR, white);
}

void PointLight::place() const {
  std::array<float, 4> pos{this->position.x, this->position.y, this->position.z,
                           this->position.w};

  glLightfv(GL_LIGHT0 + index, GL_POSITION, pos.data());
}
