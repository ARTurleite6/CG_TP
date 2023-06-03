#include "box.h"

Box::Box(const std::vector<float> &args) noexcept
    : dimensions(args[0]), divisions(args[1]) {

  std::array<Plane, 6> planes{Plane{args}, Plane{args}, Plane{args},
                              Plane{args}, Plane{args}, Plane{args}};

  // planes[0] base
  planes[0].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{0.0f, -dimensions / 2.0f, 0.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f}, 180.0f));

  // planes[1] top
  planes[1].computeOperation(maths::translate(
      Matrix(1.0f), Vertex{0.0f, dimensions / 2.0f, 0.0f, 0.0f}));

  // plantes[2] left
  planes[2].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{-dimensions / 2.0f, 0.0f, 0.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 0.0f, -1.0f, 0.0f}, 90.0f) *
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 1.0f, 0.0f, 0.0f}, -90.0f));

  // planes[3] front
  planes[3].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{0.0f, 0.0f, dimensions / 2.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f}, 90.0f));

  // plantes[4] right
  planes[4].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{dimensions / 2.0f, 0.0f, 0.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 0.0f, 1.0f, 0.0f}, -90.0f) *
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 1.0f, 0.0f, 0.0f}, 90.0f));

  // planes[5] back
  planes[5].computeOperation(
      maths::translate(Matrix(1.0f),
                       Vertex{0.0f, 0.0f, -dimensions / 2.0f, 0.0f}) *
      maths::rotate(Matrix(1.0f), Vertex{1.0f, 0.0f, 0.0f, 0.0f}, -90.0f) * 
      maths::rotate(Matrix(1.0f), Vertex{0.0f, 1.0f, 0.0f, 0.0f}, 180.0f));

  this->texCoords.clear();
  this->texCoords.reserve(24);

  planes[0].computeTextureCoords((1.0f / 4.0f), 1.0f / 2.0f, 0.0f, 1.0f / 3.0f);
  planes[1].computeTextureCoords((1.0f / 4.0f), 1.0f / 2.0f, 2.0f / 3.0f, 1.0f);
  planes[2].computeTextureCoords(0.0f, 1.0f / 4.0f, 1.0f / 3.0f, 2.0f / 3.0f);
  planes[3].computeTextureCoords(1.0f / 4.0f, 1.0f / 2.0f, 1.0f / 3.0f,
                                 2.0f / 3.0f);

  for (const auto &tex : planes[3].texCoords) {
    std::cout << tex << '\n';
  }

  for (int i = 4; i < 6; ++i) {
    const float t_factor = 2.0f * static_cast<float>(i);

    planes[i].computeTextureCoords(static_cast<float>(i - 2) / 4.0f,
                                   static_cast<float>(i - 1) / 4.0f,
                                   1.0f / 3.0f, 2.0f / 3.0f);
  }

  for (const auto &plane : planes) {
    this->vertices.insert(this->vertices.end(), plane.vertices.begin(),
                          plane.vertices.end());
    this->normals.insert(this->normals.end(), plane.normals.begin(),
                         plane.normals.end());

    this->texCoords.insert(this->texCoords.end(), plane.texCoords.begin(),
                           plane.texCoords.end());
  }

  std::cout << "Texture points = " << this->texCoords.size() << '\n';
  std::cout << "Normals points = " << this->normals.size() << '\n';
  std::cout << "Points points = " << this->vertices.size() << '\n';
}
