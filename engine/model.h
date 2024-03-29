#ifndef MODEL_H
#define MODEL_H

#include "color.h"
#include "include.h"
#include "io.h"
#include "my_math.h"
#include "parse_errors/xml_parse_error.h"
#include "renderer.h"
#include <fmt/format.h>
#include <tinyxml2.h>

class Model {

private:
  struct Coordinates {
    float x, y, z;
  };

public:
  Model() = default;
  explicit Model(tinyxml2::XMLElement *element);
  Model(Model &&) = default;
  Model(const Model &) = default;
  Model &operator=(Model &&) = default;
  Model &operator=(const Model &) = default;
  ~Model() = default;

  void draw(Renderer &renderer) const noexcept;

private:
  inline void setupMaterial() const noexcept { this->color.setup(); }

private:
  std::string filename;
  std::optional<std::string> texture_file{std::nullopt};
  std::vector<maths::Vertex> vertices;
  std::vector<maths::Vertex> normals;
  Color color;
};

#endif
