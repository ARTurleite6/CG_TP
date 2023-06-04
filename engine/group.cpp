#include "group.h"

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
      if(transforms->FirstChild() == nullptr) return;
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

void Group::draw(Renderer &renderer, int elapsedTime,
                 bool draw_lines) const noexcept {
  glPushMatrix();
  this->apply_transformations(elapsedTime, draw_lines);
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

void Group::apply_transformations(int elapsedTime,
                                  bool draw_lines) const noexcept {
  for (const auto &transformation : this->transformations) {
    if (draw_lines &&
        transformation->getType() == TypeTransformation::TimedTranslate) {
      const auto translation =
          dynamic_cast<transformations::TimedTranslation *>(
              transformation.get());
      if (translation != nullptr)
        translation->drawLine();
    }
    //transformation->apply(elapsedTime);
    transformation->apply(0);
  }
}
