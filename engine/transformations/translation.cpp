#include "translation.h"
#include <stdexcept>

#define TESS 100.0f

namespace transformations {

Translation::Translation(float x, float y, float z) : x(x), y(y), z(z) {}

Translation::Translation(const tinyxml2::XMLElement *transform) {

  auto time = transform->FindAttribute("time");

  if (time == nullptr) {
    transform->QueryAttribute("x", &this->x);
    transform->QueryAttribute("y", &this->y);
    transform->QueryAttribute("z", &this->z);
    this->curve = false;
  } else {
    this->curve = true;
    this->time = time->FloatValue();
    this->align = transform->QueryAttribute("align", &this->align);

    auto point = transform->FirstChildElement("point");
    while (point != nullptr) {
      maths::Vertex v{0.0f, 0.0f, 0.0f, 1.0f};
      point->QueryAttribute("x", &v.x);
      point->QueryAttribute("y", &v.y);
      point->QueryAttribute("z", &v.z);

      this->points.push_back(v);
      point = point->NextSiblingElement("point");
    }

    if (this->points.size() < 4) {
      throw std::invalid_argument(
          "You must pass at least 4 points to the curve");
    }
  }
}

float Translation::getLocalT(float globalT) const noexcept {
  float t = globalT * static_cast<float>(this->points.size());
  const int index = floor(static_cast<double>(t));
  t = t - static_cast<float>(index);

  return t;
}

std::array<maths::Vertex, 4>
Translation::getSegment(float globalT) const noexcept {

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

maths::Vertex Translation::getPositionCurve(float globalT) const noexcept {
  maths::Matrix matrix{std::array<std::array<float, 4>, 4>{
      std::array<float, 4>{-0.5f, 1.5f, -1.5f, 0.5f},
      std::array<float, 4>{1.0f, -2.5f, 2.0f, -0.5f},
      std::array<float, 4>{-0.5f, 0.0f, 0.5f, 0.0f},
      std::array<float, 4>{0.0f, 1.0f, 0.0f, 0.0f},
  }};

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

void Translation::drawLine() const noexcept {

  if (this->curve) {
    auto t = 0.0f;

    glBegin(GL_LINE_LOOP);

    while (t < 1.0f) {
      auto position = this->getPositionCurve(t);

      glVertex3f(position.x, position.y, position.z);

      t += 1.0f / TESS;
    }

    glEnd();
  }
}

void Translation::apply(int elapsedTime) noexcept {
  maths::Vertex position = {this->x, this->y, this->z, 1.0f};
  float seconds = static_cast<float>(elapsedTime) / 1000.0f;
  if (this->curve) {
    position = this->getPositionCurve(seconds / this->time);
  }
  glTranslatef(position.x, position.y, position.z);
}

} // namespace transformations
