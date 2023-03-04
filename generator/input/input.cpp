#include "input.h"
#include "../figures/box.h"
#include <cstdint>
#include <fstream>
#include <iostream>

namespace input {

Figures fromString(std::string_view str) {
  if (str == "sphere") {
    return Figures::Sphere;
  } else if (str == "plane") {
    return Figures::Plane;
  } else if (str == "box") {
    return Figures::Box;
  } else if (str == "cone") {
    return Figures::Cone;
  } else {
    throw std::invalid_argument("Invalid figure");
  }
}

Input::Input(int argc, char *argv[]) {
  if (argc < 5) {
    throw std::invalid_argument("Not enough arguments");
  }

  this->figure = fromString(argv[1]);
  this->outFile = argv[argc - 1];

  Figures fig = fromString(argv[1]);

  for (int i = 2; i < argc - 1; ++i) {
    dimensions.push_back(std::stoul(argv[i]));
  }
}

std::ostream &operator<<(std::ostream &os, const Input &input) {
  os << "Figure: " << static_cast<int>(input.figure) << std::endl;
  os << "Dimensions: ";
  for (const auto &dim : input.dimensions) {
    os << dim << " ";
  }
  os << std::endl;
  os << "Output file: " << input.outFile << std::endl;
  return os;
}

std::ostream &operator<<(std::ostream &os, const Figures &fig) {
    switch (fig) {
    case Figures::Sphere:
        os << "Sphere";
        break;
    case Figures::Plane:
        os << "Plane";
        break;
    case Figures::Box:
        os << "Box";
        break;
    case Figures::Cone:
        os << "Cone";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

std::unique_ptr<Figure> Input::getFigure() const noexcept {
    std::cout << "Deciding...\n";
  if (this->figure == Figures::Plane) {
      std::cout << "Entering plane...\n";
    return std::make_unique<Plane>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1])});
  } else if (this->figure == Figures::Box) {
      std::cout << "Making a box...\n";
    return std::make_unique<Box>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1])});
  }

  return nullptr;
}

}; // namespace input
