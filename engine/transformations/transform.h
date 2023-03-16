#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <tinyxml2.h>

namespace transformations {
class Transform {
public:
  Transform() = default;
  Transform(Transform &&) = default;
  Transform(const Transform &) = default;
  Transform &operator=(Transform &&) = default;
  Transform &operator=(const Transform &) = default;
  virtual ~Transform() = default;
  virtual void apply() const noexcept = 0;
};

std::unique_ptr<Transform>
create_transform(const tinyxml2::XMLElement *transform);

} // namespace transformations
#endif // TRANSFORM_H
