#ifndef FIXED_TRANSLATION_H
#define FIXED_TRANSLATION_H

#include "../include.h"
#include "../parsing.h"
#include "tinyxml2.h"
#include "transform.h"
namespace transformations {

class FixedTranslation : public Transform {

public:
  explicit FixedTranslation(const tinyxml2::XMLElement *translation);

  ~FixedTranslation() override = default;

  void apply(int elapsedTime) noexcept override;

  [[nodiscard]] inline TypeTransformation getType() const noexcept override {
    return TypeTransformation::FixedTranslate;
  }

private:
  float x{0}, y{0}, z{0};
};

} // namespace transformations

#endif // FIXED_TRANSLATION_H
