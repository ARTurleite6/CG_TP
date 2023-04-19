#ifndef TRANSLATION_H
#define TRANSLATION_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../utils.h"

#include "transform.h"

namespace transformations {
class Translation : public Transform {
public:
  Translation(float, float, float);
  explicit Translation(const tinyxml2::XMLElement *transform);
  ~Translation() override = default;
  void apply(int elapsedTime) noexcept override;

  void drawLine() const noexcept;

  [[nodiscard]] TypeTransformation getType() const noexcept override {
    return TypeTransformation::Translate;
  }

private:
  [[nodiscard]] utils::Vertex getPositionCurve(float globalT) const noexcept;

  [[nodiscard]] std::array<utils::Vertex, 4>
  getSegment(float globalT) const noexcept;

  [[nodiscard]] float getLocalT(float globalT) const noexcept;

  float x{0}, y{0}, z{0};

  bool curve{false};
  float time{0.0f};
  bool align{false};
  std::vector<utils::Vertex> points;
  utils::Vertex prevY{0.0f, 1.0f, 0.0f, 0.0f};
};

}; // namespace transformations

#endif // TRANSLATION_H
