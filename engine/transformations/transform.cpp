#include "transform.h"
#include "FixedTranslation.h"
#include "TimedTranslation.h"
#include "rotation.h"
#include "scale.h"

namespace transformations {

std::unique_ptr<Transform>
create_transform(const tinyxml2::XMLElement *transform) {
  std::string_view name = transform->Value();
  float x{0.0f}, y{0.0f}, z{0.0f};
  transform->QueryFloatAttribute("x", &x);
  transform->QueryFloatAttribute("y", &y);
  transform->QueryFloatAttribute("z", &z);

  if (name == "translate") {
    const auto time = transform->Attribute("time");
    if (time != nullptr)
      return std::make_unique<TimedTranslation>(transform);
    else
      return std::make_unique<FixedTranslation>(transform);
  } else if (name == "rotate") {
    return std::make_unique<Rotation>(transform);
  } else if (name == "scale") {
    return std::make_unique<Scale>(x, y, z);
  }
  return nullptr;
}

} // namespace transformations
