#ifndef MODEL_H
#define MODEL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Model {

private:
  struct Coordinates {
    float x, y, z;
  };

public:
  Model() = default;
  explicit Model(std::string_view filename);
  Model(Model &&) = default;
  Model(const Model &) = default;
  Model &operator=(Model &&) = default;
  Model &operator=(const Model &) = default;
  ~Model() = default;

  [[nodiscard]] const std::vector<Coordinates> &getVertices() const noexcept {
    return this->vertices;
  }

  void draw() const noexcept;

private:
  std::string filename;
  std::vector<Coordinates> vertices;
};

#endif
