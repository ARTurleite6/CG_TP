#ifndef GROUP_H
#define GROUP_H

#include "model.h"
#include "renderer.h"
#include "transformations/transform.h"

class Transform;

class Group {
public:
  explicit Group(tinyxml2::XMLElement *group);

  void draw(Renderer &renderer, int elapsedTime) const noexcept;

private:
  void push_transformation(
      const std::shared_ptr<transformations::Transform> &transform) noexcept;
  void load_models(tinyxml2::XMLElement *group) noexcept;
  void load_children(tinyxml2::XMLElement *group) noexcept;
  void load_transform(tinyxml2::XMLElement *group) noexcept;
  void apply_transformations(int elapsedTime) const noexcept;
  void draw_children(Renderer &renderer, int elapsedTime) const noexcept;

  std::vector<Model> models;
  std::vector<std::shared_ptr<transformations::Transform>> transformations;
  std::vector<Group> children;
};

#endif
