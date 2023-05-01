#ifndef TIMED_TRANSLATION_H
#define TIMED_TRANSLATION_H

#include "tinyxml2.h"

#include "../include.h"
#include "../parsing.h"
#include "my_math.h"
#include "transform.h"

namespace transformations {

class TimedTranslation : public Transform {

public:
  explicit TimedTranslation(const tinyxml2::XMLElement *translation);
  ~TimedTranslation() override = default;

  void drawLine() const noexcept;
  void apply(int elapsedTime) noexcept override;

private:
  [[nodiscard]] maths::Vertex getPositionCurve(float globalT) const noexcept;

  [[nodiscard]] std::array<maths::Vertex, 4>
  getSegment(float globalT) const noexcept;

  [[nodiscard]] float getLocalT(float globalT) const noexcept;

  [[nodiscard]] inline TypeTransformation getType() const noexcept override {
    return TypeTransformation::TimedTranslate;
  }

private:
  float time{0};
  bool aligned{false};

  std::vector<maths::Vertex> points;
};

} // namespace transformations

#endif // TIMED_TRANSLATION_H
