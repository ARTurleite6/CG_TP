#ifndef INPUT_H
#define INPUT_H
#include <cstdint>
#include <ostream>
#include <string>
#include <stdexcept>

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

private:
  Figures figure;
  std::vector<std::uint32_t> dimensions;
  std::string outFile;
};

}; // namespace input

#endif // INPUT_H
