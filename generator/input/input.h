#ifndef INPUT_H
#define INPUT_H
#include "../figures/Triangle.h"
#include "../figures/Plane.h"
#include "../figures/figure.h"
#include "utils.h"
#include <array>
#include <cstdint>
#include <functional>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>

#include <string_view>
#include <vector>

namespace input {

using namespace utils;

enum class Figures {
  Sphere = 3,
  Plane = 2,
  Box = 2,
  Cone = 4,
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

  [[nodiscard]] inline const std::vector<std::uint32_t> &
  getDimensions() const noexcept {
    return dimensions;
  }

  [[nodiscard]] std::unique_ptr<Figure> getFigure() const noexcept;

private:
  Figures figure;
  std::vector<std::uint32_t> dimensions;
  std::string outFile;

  std::vector<Triangle> triangles;
};

}; // namespace input

#endif // INPUT_H
