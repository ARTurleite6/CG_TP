#ifndef GROUP_H
#define GROUP_H

#include "model.h"
#include "transformations/transform.h"
#include <GLUT/glut.h>
#include <tinyxml2.h>

class Transform;

class Group {
public:
  explicit Group(tinyxml2::XMLElement *group);

  void draw() const noexcept;

private:
  void push_transformation(
      const std::shared_ptr<transformations::Transform> &transform) noexcept;
  void load_models(tinyxml2::XMLElement *group) noexcept;
  void load_children(tinyxml2::XMLElement *group) noexcept;
  void load_transform(tinyxml2::XMLElement *group) noexcept;
  void apply_transformations() const noexcept;
  void draw_children() const noexcept;
  std::vector<Model> models;
  std::vector<std::shared_ptr<transformations::Transform>> transformations;
  std::vector<Group> children;
};

#endif
