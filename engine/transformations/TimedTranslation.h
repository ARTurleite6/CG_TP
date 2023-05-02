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

  void drawLine() noexcept;
  void apply(int elapsedTime) noexcept override;

private:
  [[nodiscard]] maths::Vertex getPositionCurve(float globalT,
                                               bool drawing = false) noexcept;

  [[nodiscard]] std::array<maths::Vertex, 4>
  getSegment(float globalT) const noexcept;

  [[nodiscard]] float getLocalT(float globalT) const noexcept;

  [[nodiscard]] inline TypeTransformation getType() const noexcept override {
    return TypeTransformation::TimedTranslate;
  }

  [[nodiscard]] maths::Matrix<float, 4, 4>
  getRotationMatrix(float globalT) noexcept;

private:
  float time{0};
  bool aligned{false};
  maths::Vertex lastY{0.0f, 1.0f, 0.0f, 0.0f};
  maths::Vertex current_derivative{0.0f, 0.0f, 0.0f, 0.0f};

  std::vector<maths::Vertex> points;
};

} // namespace transformations

#endif // TIMED_TRANSLATION_H
