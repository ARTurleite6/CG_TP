#include "spotlight.h"

SpotLight::SpotLight(tinyxml2::XMLElement *element) : Light(), cutoff(45) {
  element->QueryFloatAttribute("posX", &this->position.x);
  element->QueryFloatAttribute("posY", &this->position.y);
  element->QueryFloatAttribute("posZ", &this->position.z);

  element->QueryFloatAttribute("dirX", &this->direction.x);
  element->QueryFloatAttribute("dirY", &this->direction.y);
  element->QueryFloatAttribute("dirZ", &this->direction.z);

  element->QueryFloatAttribute("cutoff", &this->cutoff);
}

void SpotLight::place() const {

  std::array<float, 4> position{this->position.x, this->position.y,
                                this->position.z, 1.0f};

  std::array<float, 4> direction{this->direction.x, this->direction.y,
                                 this->direction.z, 0.0f};

  const auto index = GL_LIGHT0 + this->getIndex();

  glLightfv(index, GL_POSITION, position.data());
  glLightfv(index, GL_SPOT_DIRECTION, direction.data());
  glLightf(index, GL_SPOT_CUTOFF, this->cutoff);
}
