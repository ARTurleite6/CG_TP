#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H
#include "include.h"
#include "light.h"
#include "my_math.h"
#include <tinyxml2.h>

class DirectionalLight : public Light {
public:
  DirectionalLight(tinyxml2::XMLElement *element, std::uint32_t index);
  ~DirectionalLight() override = default;

  void place() const override;

private:
  maths::Vertex direction;
};

#endif // DIRECTIONLIGHT_H
