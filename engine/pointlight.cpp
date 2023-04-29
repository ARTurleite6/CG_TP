#include "pointlight.h"

PointLight::PointLight(tinyxml2::XMLElement *element, std::uint32_t index)
    : Light(index) {

  this->position.x = element->FloatAttribute("posX", 0);
  this->position.y = element->FloatAttribute("posY", 0);
  this->position.z = element->FloatAttribute("posZ", 0);
  this->position.w = 1.0f;
}

void PointLight::place() const {
  std::array<float, 4> pos{this->position.x, this->position.y, this->position.z,
                           1.0f};

  glLightfv(GL_LIGHT0 + this->getIndex(), GL_POSITION, pos.data());
}
