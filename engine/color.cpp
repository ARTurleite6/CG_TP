#include "color.h"

Color::Color(tinyxml2::XMLElement *element) {
  if (element == nullptr)
    return;

  auto diffuse = element->FirstChildElement("diffuse");
  if (diffuse != nullptr) {
    this->diffuse.r = diffuse->FloatAttribute("r", 0);
    this->diffuse.g = diffuse->FloatAttribute("g", 0);
    this->diffuse.b = diffuse->FloatAttribute("b", 0);
  }

  auto ambient = element->FirstChildElement("ambient");
  if (ambient != nullptr) {
    this->ambient.r = ambient->FloatAttribute("r", 0);
    this->ambient.g = ambient->FloatAttribute("g", 0);
    this->ambient.b = ambient->FloatAttribute("b", 0);
  }

  auto specular = element->FirstChildElement("specular");
  if (specular != nullptr) {
    this->specular.r = specular->FloatAttribute("r", 0);
    this->specular.g = specular->FloatAttribute("g", 0);
    this->specular.b = specular->FloatAttribute("b", 0);
  }

  auto emissive = element->FirstChildElement("emissive");
  if (emissive != nullptr) {
    this->emissive.r = emissive->FloatAttribute("r", 0);
    this->emissive.g = emissive->FloatAttribute("g", 0);
    this->emissive.b = emissive->FloatAttribute("b", 0);
  }

  auto shininess = element->FirstChildElement("shininess");
  if (shininess != nullptr) {
    this->shininess = shininess->FloatAttribute("value", 0);
  }
}
