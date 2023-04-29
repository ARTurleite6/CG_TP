#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "include.h"
#include "light.h"
#include "my_math.h"
#include "tinyxml2.h"
class PointLight : public Light {

public:
  explicit PointLight(tinyxml2::XMLElement *element, std::uint32_t index = 0);
  ~PointLight() override = default;

  void place() const override;

private:
  maths::Vertex position;
};

#endif // POINTLIGHT_H
