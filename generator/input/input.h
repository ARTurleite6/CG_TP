#ifndef INPUT_H
#define INPUT_H
#include <cstdint>
#include <ostream>
#include <stdexcept>
#include <string>

#include <string_view>
#include <vector>

namespace input {

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

private:
  Figures figure;
  std::vector<std::uint32_t> dimensions;
  std::string outFile;
};

}; // namespace input

#endif // INPUT_H
