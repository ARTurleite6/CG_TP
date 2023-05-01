#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <tinyxml2.h>

enum class TypeTransformation {
  TimedTranslate,
  FixedTranslate,
  Rotate,
  Scale,
};

namespace transformations {
class Transform {
public:
  virtual ~Transform() = default;
  virtual void apply(int elapsedTime) noexcept = 0;

  [[nodiscard]] virtual TypeTransformation getType() const noexcept = 0;
};

std::unique_ptr<Transform>
create_transform(const tinyxml2::XMLElement *transform);

} // namespace transformations
#endif // TRANSFORM_H
