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

void Group::push_transformation(
    const std::shared_ptr<transformations::Transform> &transform) noexcept {
  this->transformations.push_back(transform);
  for (auto &group : this->children) {
    group.push_transformation(transform);
  }
}

void Group::load_transform(tinyxml2::XMLElement *group) noexcept {
  auto *transforms = group->FirstChildElement("transform");

  if (transforms != nullptr) {
    auto *transformation = transforms->FirstChild()->ToElement();
    while (transformation != nullptr) {
      this->push_transformation(
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
  glPushMatrix();
  this->apply_transformations();
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  for (const auto &model : this->models) {
    model.draw();
  }
  glEnd();
  this->draw_children();
  glPopMatrix();
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
