#ifndef INPUT_H
#define INPUT_H
#include "../figures/Plane.h"
#include "../figures/sphere.h"
#include "../figures/Triangle.h"
#include "../figures/pyramid.h"
#include "../figures/box.h"
#include "../figures/cone.h"
#include "../figures/figure.h"
#include "../figures/torus.h"
#include "../figures/bezzier.h"
#include "my_math.h"

namespace input {

using namespace maths;

enum class Figures {
  Sphere = 3,
  Plane = 1,
  Box = 2,
  Cone = 4,
  Torus = 5,
  Pyramid = 6,
  Bezzier = 7,
};

Figures fromString(std::string_view str);

class Input {

public:
  Input(int argc, char *argv[]);
  ~Input() = default;

  friend std::ostream &operator<<(std::ostream &os, const Input &input);

  [[nodiscard]] inline const std::string &getOutFile() const noexcept {
    return outFile;
  }

  [[nodiscard]] inline const std::vector<float> &
  getDimensions() const noexcept {
    return dimensions;
  }

  [[nodiscard]] std::unique_ptr<Figure> getFigure() const noexcept;

private:
  int parse(int argc, char *argv[]);

private:
  Figures figure;
  std::vector<float> dimensions;
  std::string inputFile;
  std::string outFile;

  std::vector<Triangle> triangles;
};

}; // namespace input

#endif // INPUT_H
