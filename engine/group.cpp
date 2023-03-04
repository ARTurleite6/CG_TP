#include "group.h"

Group::Group(tinyxml2::XMLElement *group) {
  tinyxml2::XMLElement *models = group->FirstChildElement("models");
  auto model = models->FirstChildElement("model");
  while (model) {
    this->models.emplace_back(model->Attribute("file"));
    model = model->NextSiblingElement("model");
  }
}

void Group::draw() const noexcept {
  std::cout << "comecei" << '\n';
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 1.0f, 1.0f);
  for (const auto &model : this->models) {
      model.draw();
  }
  glEnd();
}
