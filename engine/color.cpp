#include "color.h"

Color::Color(tinyxml2::XMLElement *element) {

  if (element != nullptr) {
    auto diffuse = element->FirstChildElement("diffuse");
    if (diffuse != nullptr) {
      this->diffuse.r = diffuse->FloatAttribute("R", 200);
      this->diffuse.g = diffuse->FloatAttribute("G", 200);
      this->diffuse.b = diffuse->FloatAttribute("B", 200);
    }

    auto ambient = element->FirstChildElement("ambient");
    if (ambient != nullptr) {

      this->ambient.r = ambient->FloatAttribute("R", 50);
      this->ambient.g = ambient->FloatAttribute("G", 50);
      this->ambient.b = ambient->FloatAttribute("B", 50);
    }

    auto specular = element->FirstChildElement("specular");
    if (specular != nullptr) {
      this->specular.r = specular->FloatAttribute("R", 0);
      this->specular.g = specular->FloatAttribute("G", 0);
      this->specular.b = specular->FloatAttribute("B", 0);
    }

    auto emissive = element->FirstChildElement("emissive");
    if (emissive != nullptr) {
      this->emissive.r = emissive->FloatAttribute("R", 0);
      this->emissive.g = emissive->FloatAttribute("G", 0);
      this->emissive.b = emissive->FloatAttribute("B", 0);
    }

    auto shininess = element->FirstChildElement("shininess");
    if (shininess != nullptr) {
      this->shininess = shininess->FloatAttribute("value", 0);
    }
  }

  this->ambient.normalize();
  this->specular.normalize();
  this->diffuse.normalize();
  this->emissive.normalize();
}

void Color::setup() const noexcept {

  std::array<float, 4> arrParams{0.0f, 0.0f, 0.0f, 1.0f};

  arrParams = {this->ambient.r, this->ambient.g, this->ambient.b, 1.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, arrParams.data());

  arrParams = {this->diffuse.r, this->diffuse.g, this->diffuse.b, 1.0f};
  glMaterialfv(GL_FRONT, GL_DIFFUSE, arrParams.data());

  arrParams = {this->specular.r, this->specular.g, this->specular.b, 1.0f};
  glMaterialfv(GL_FRONT, GL_SPECULAR, arrParams.data());

  arrParams = {this->emissive.r, this->emissive.g, this->emissive.b, 1.0f};
  glMaterialfv(GL_FRONT, GL_EMISSION, arrParams.data());
  glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
}
