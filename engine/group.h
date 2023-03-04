#ifndef GROUP_H
#define GROUP_H

#include "model.h"
#include <tinyxml2.h>
#include <GLUT/glut.h>
class Group {
public:
  Group() = default;
  explicit Group(tinyxml2::XMLElement *group);
  Group(Group &&) = default;
  Group(const Group &) = default;
  Group &operator=(Group &&) = default;
  Group &operator=(const Group &) = default;
  ~Group() = default;

  void draw() const noexcept;

private:
  std::vector<Model> models;
};

#endif
