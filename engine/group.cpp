#include "group.h"
#include "transformations/transform.h"
#include "transformations/translation.h"

Group::Group(tinyxml2::XMLElement *group) {

  this->load_transform(group);
  this->load_models(group);
  this->load_children(group);
}

void Group::load_models(tinyxml2::XMLElement *group) noexcept {
  tinyxml2::XMLElement *models = group->FirstChildElement("models");
  if (models != nullptr) {
    auto model = models->FirstChildElement("model");
    while (model) {
      this->models.emplace_back(model);
      model = model->NextSiblingElement("model");
    }
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

void Group::draw(Renderer &renderer, int elapsedTime) const noexcept {
  glPushMatrix();
  this->apply_transformations(elapsedTime);
  glColor3f(1.0f, 1.0f, 1.0f);
  // glBegin(GL_TRIANGLES);
  for (const auto &model : this->models) {
    model.draw(renderer);
  }
  // glEnd();
  this->draw_children(renderer, elapsedTime);
  glPopMatrix();
}

void Group::draw_children(Renderer &renderer, int elapsedTime) const noexcept {
  for (const auto &child : this->children) {
    child.draw(renderer, elapsedTime);
  }
}

void Group::apply_transformations(int elapsedTime) const noexcept {
  for (const auto &transformation : this->transformations) {
    // const auto translation =
    //     dynamic_cast<transformations::Translation *>(transformation.get());
    // if (translation != nullptr) {
    //   translation->drawLine();
    // }
    if (transformation->getType() == TypeTransformation::Translate) {
      const auto translation =
          static_cast<transformations::Translation *>(transformation.get());
      translation->drawLine();
    }
    transformation->apply(elapsedTime);
  }
}
