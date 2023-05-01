#include "TimedTranslation.h"

#define TESS 100.0f

namespace transformations {

TimedTranslation::TimedTranslation(const tinyxml2::XMLElement *translation)
    : time(queryFloatAttr(translation, "time")),
      aligned(queryBooleanAttr(translation, "align")) {

  for (auto point = translation->FirstChildElement("point"); point != nullptr;
       point = point->NextSiblingElement("point")) {
    maths::Vertex v{0.0f, 0.0f, 0.0f, 1.0f};
    v.x = queryFloatAttr(point, "x");
    v.y = queryFloatAttr(point, "y");
    v.z = queryFloatAttr(point, "z");
    this->points.push_back(v);
  }

  if (this->points.size() < 4) {
    throw std::invalid_argument("You must pass at least 4 points to the curve");
  }
}

void TimedTranslation::drawLine() const noexcept {
  auto t = 0.0f;

  glBegin(GL_LINE_LOOP);

  while (t < 1.0f) {
    auto position = this->getPositionCurve(t);

    glVertex3f(position.x, position.y, position.z);

    t += 1.0f / TESS;
  }

  glEnd();
}

void TimedTranslation::apply(int elapsedTime) noexcept {

  float seconds = static_cast<float>(elapsedTime) / 1000.0f;
  auto position = this->getPositionCurve(seconds / this->time);

  glTranslatef(position.x, position.y, position.z);
}

[[nodiscard]] maths::Vertex
TimedTranslation::getPositionCurve(float globalT) const noexcept {
  maths::Matrix matrix{
      -0.5f, 1.5f, -1.5f, 0.5f, 1.0f, -2.5f, 2.0f, -0.5f,
      -0.5f, 0.0f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
  };

  auto t = this->getLocalT(globalT);

  maths::Vertex tV{static_cast<float>(std::pow(t, 3)),
                   static_cast<float>(std::pow(t, 2)), t, 1.0f};

  const auto segment = this->getSegment(globalT);
  std::array<std::array<float, 3>, 4> points{};
  std::transform(segment.cbegin(), segment.cend(), points.begin(),
                 [](const maths::Vertex &v) {
                   return std::array<float, 3>{v.x, v.y, v.z};
                 });

  std::array<float, 3> array_result{};
  for (int i = 0; i < 3; ++i) {
    maths::Vertex p{
        points[0][i],
        points[1][i],
        points[2][i],
        points[3][i],
    };

    auto a = matrix * p;

    auto value = tV * a;
    array_result[i] = value;
  }

  return maths::Vertex{array_result[0], array_result[1], array_result[2],
                       array_result[3]};
}

[[nodiscard]] std::array<maths::Vertex, 4>
TimedTranslation::getSegment(float globalT) const noexcept {
  float t = globalT * static_cast<float>(this->points.size());
  const int index = floor(static_cast<double>(t));
  t = t - static_cast<float>(index);

  const auto number_points = this->points.size();

  std::array<unsigned long, 4> indices{};

  indices[0] = (index + number_points - 1) % number_points;
  indices[1] = (indices[0] + 1) % number_points;
  indices[2] = (indices[1] + 1) % number_points;
  indices[3] = (indices[2] + 1) % number_points;

  return std::array<maths::Vertex, 4>{
      this->points[indices[0]],
      this->points[indices[1]],
      this->points[indices[2]],
      this->points[indices[3]],
  };
}

[[nodiscard]] float TimedTranslation::getLocalT(float globalT) const noexcept {

  float t = globalT * static_cast<float>(this->points.size());
  const int index = floor(static_cast<double>(t));
  t = t - static_cast<float>(index);

  return t;
}

} // namespace transformations
