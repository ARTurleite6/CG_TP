#include "transform.h"
#include "rotation.h"
#include "scale.h"
#include "translation.h"

namespace transformations {

std::unique_ptr<Transform>
create_transform(const tinyxml2::XMLElement *transform) {
  std::string_view name = transform->Value();
  float x{0.0f}, y{0.0f}, z{0.0f};
  std::cout << name << '\n';
  transform->QueryFloatAttribute("x", &x);
  transform->QueryFloatAttribute("y", &y);
  transform->QueryFloatAttribute("z", &z);
  std::cout << x << ' ' << y << ' ' << z << '\n';

  if (name == "translate") {
    return std::make_unique<Translation>(x, y, z);
  } else if (name == "rotate") {
    float angle = 0.0f;
    transform->QueryFloatAttribute("angle", &angle);
    return std::make_unique<Rotation>(angle, x, y, z);
  } else if (name == "scale") {
    return std::make_unique<Scale>(x, y, z);
  }
  return nullptr;
}

} // namespace transformations
