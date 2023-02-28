#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <string_view>
#include <vector>
class Model {
public:
  Model() = default;
  explicit Model(std::string_view filename);
  Model(Model &&) = default;
  Model(const Model &) = default;
  Model &operator=(Model &&) = default;
  Model &operator=(const Model &) = default;
  ~Model() = default;

private:
  struct Coordinates {
    float x, y, z;
  };

  std::string filename;
  std::vector<Coordinates> vertices;
};

#endif
