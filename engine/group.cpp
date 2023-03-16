#include "group.h"
#include "transformations/transform.h"

Group::Group(tinyxml2::XMLElement *group) {

  this->load_transform(group);
  this->load_models(group);
  this->load_children(group);
}

void Group::load_models(tinyxml2::XMLElement *group) noexcept {
  tinyxml2::XMLElement *models = group->FirstChildElement("models");
  auto model = models->FirstChildElement("model");
  while (model) {
    this->models.emplace_back(model->Attribute("file"));
    model = model->NextSiblingElement("model");
  }
}

void Group::load_transform(tinyxml2::XMLElement *group) noexcept {
  auto *transforms = group->FirstChildElement("transform");

  if (transforms != nullptr) {
    auto *transformation = transforms->FirstChild()->ToElement();
    int i = 0;
    while (transformation != nullptr && i < 3) {
      this->transformations.push_back(
          transformations::create_transform(transformation));
      transformation = transformation->NextSiblingElement();
    }
  }
}

void Group::load_children(tinyxml2::XMLElement *group) noexcept {
  auto *child = group->FirstChildElement("group");
  while (child != nullptr) {
    this->children.emplace_back(child);
    child = child->NextSiblingElement("group");
  }
}

void Group::draw() const noexcept {
  std::cout << "comecei" << '\n';
  glPushMatrix();
  this->apply_transformations();
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 1.0f, 1.0f);
  for (const auto &model : this->models) {
    model.draw();
  }
  this->draw_children();
  glPopMatrix();
  glEnd();
}

void Group::draw_children() const noexcept {
  for (const auto &child : this->children) {
    child.draw();
  }
}

void Group::apply_transformations() const noexcept {
  for (const auto &transformation : this->transformations) {
    transformation->apply();
  }
}
