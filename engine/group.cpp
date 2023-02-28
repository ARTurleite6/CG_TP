#include "group.h"

Group::Group(tinyxml2::XMLElement *group) {
  tinyxml2::XMLElement *model = group->FirstChildElement("models");
  while (model) {
    this->models.emplace_back(model->Attribute("file"));
    model = model->NextSiblingElement("model");
  }
}
