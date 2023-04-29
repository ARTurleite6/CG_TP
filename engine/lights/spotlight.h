#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "../include.h"
#include "light.h"
#include "my_math.h"
#include "tinyxml2.h"
class SpotLight : public Light {

public:
  SpotLight(tinyxml2::XMLElement *element, std::uint32_t index);
  ~SpotLight() override = default;

  void place() const override;

private:
  maths::Vertex position, direction;
  float cutoff;
};

#endif // SPOTLIGHT_H
