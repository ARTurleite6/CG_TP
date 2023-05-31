#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H
#include "../include.h"
#include "light.h"
#include "my_math.h"
#include <tinyxml2.h>

class DirectionalLight : public Light {
public:
  explicit DirectionalLight(tinyxml2::XMLElement *element);
  ~DirectionalLight() override = default;

  void place() const override;

private:
  maths::Vertex direction;
};

#endif // DIRECTIONLIGHT_H
