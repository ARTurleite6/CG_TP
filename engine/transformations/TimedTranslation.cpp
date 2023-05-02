#include "TimedTranslation.h"
#include "my_math.h"

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

void TimedTranslation::drawLine() noexcept {
  auto t = 0.0f;

  glBegin(GL_LINE_LOOP);

  while (t < 1.0f) {
    auto position = this->getPositionCurve(t, true);

    glVertex3f(position.x, position.y, position.z);

    t += 1.0f / TESS;
  }

  glEnd();
}

void TimedTranslation::apply(int elapsedTime) noexcept {

  float seconds = static_cast<float>(elapsedTime) / 1000.0f;
  auto position = this->getPositionCurve(seconds / this->time);

  glTranslatef(position.x, position.y, position.z);

  if (this->aligned) {
    auto rotationMatrix = this->getRotationMatrix(seconds / this->time);
    rotationMatrix.transpose();

    float *matrixRot = &rotationMatrix[0][0];
    glMultMatrixf(matrixRot);
  }
}

[[nodiscard]] maths::Vertex
TimedTranslation::getPositionCurve(float globalT, bool drawing) noexcept {
  maths::Matrix matrix{
      -0.5f, 1.5f, -1.5f, 0.5f, 1.0f, -2.5f, 2.0f, -0.5f,
      -0.5f, 0.0f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
  };

  auto t = this->getLocalT(globalT);

  maths::Matrix<float, 1, 4> tV{static_cast<float>(std::pow(t, 3)),
                                static_cast<float>(std::pow(t, 2)), t, 1.0f};

  maths::Matrix<float, 1, 4> tDV{3 * static_cast<float>(std::pow(t, 2)), 2 * t,
                                 1.0f, 0.0f};

  const auto segment = this->getSegment(globalT);
  maths::Matrix<maths::Vertex, 4, 1> points{
      segment[0],
      segment[1],
      segment[2],
      segment[3],
  };

  auto a = matrix * points;

  if (!drawing)
    this->current_derivative = (tDV * a)[0][0];

  auto point = (tV * a)[0][0];

  return point;
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

[[nodiscard]] maths::Matrix<float, 4, 4>
TimedTranslation::getRotationMatrix(float globalT) noexcept {

  auto x = this->current_derivative;
  x.normalize();

  auto z = x.crossProduct(this->lastY);
  z.normalize();

  auto y = z.crossProduct(x);
  y.normalize();

  lastY = y;

  return maths::Matrix{x.x, y.x, z.x, 0.0f, x.y,  y.y,  z.y,  0.0f,
                       x.z, y.z, z.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
}

} // namespace transformations
