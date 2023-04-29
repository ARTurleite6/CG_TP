#include "directionallight.h"

DirectionalLight::DirectionalLight(tinyxml2::XMLElement *element,
                                   std::uint32_t index)
    : Light(index) {
  element->QueryFloatAttribute("dirX", &this->direction.x);
  element->QueryFloatAttribute("dirY", &this->direction.y);
  element->QueryFloatAttribute("dirZ", &this->direction.z);
  this->direction.w = 0.0f;
}

void DirectionalLight::place() const {
  std::array<float, 4> direction{this->direction.x, this->direction.y,
                                 this->direction.z, 0.0f};

  glLightfv(GL_LIGHT0 + this->getIndex(), GL_POSITION, direction.data());
}
