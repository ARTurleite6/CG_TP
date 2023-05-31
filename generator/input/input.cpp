#include "input.h"
#include "CLI/App.hpp"
#include <string>

namespace input {

Input::Input(int argc, char *argv[]) { this->parse(argc, argv); }

int Input::parse(int argc, char *argv[]) {

  CLI::App app{"Generator"};

  auto plane = app.add_subcommand("plane");
  plane->add_option("length", "Length of the plane")->required();
  plane->add_option("divisions", "Divisions of the plane")->required();
  plane->add_option("output_file", "File to store the data of plane")
      ->required();

  auto box = app.add_subcommand("box");
  box->add_option("length", "Length of the box")->required();
  box->add_option("divisions", "Divisions of the box")->required();
  box->add_option("output_file", "File to store the data of box")->required();

  auto sphere = app.add_subcommand("sphere");
  sphere->add_option("radius", "Radius of the sphere")->required();
  sphere->add_option("slices", "Slices of the sphere")->required();
  sphere->add_option("stacks", "Stacks of sphere")->required();
  sphere->add_option("output_file", "File to store the data of sphere")
      ->required();

  auto cone = app.add_subcommand("cone");
  cone->add_option("radius", "Radius of the cone")->required();
  cone->add_option("height", "Height of the cone")->required();
  cone->add_option("slices", "Slices of cone")->required();
  cone->add_option("stacks", "Stacks of cone")->required();
  cone->add_option("output_file", "File to store the data of cone")->required();

  auto bezzier = app.add_subcommand("bezzier");
  bezzier
      ->add_option("patches_file",
                   "File with bezzier patches and control points")
      ->required();
  bezzier->add_option("tesselation", "Tesselation to be used")->required();
  bezzier
      ->add_option("output_file", "File to store the data of bezzier surface")
      ->required();

  auto torus = app.add_subcommand("torus");
  torus->add_option("major_radius", "Major radius of Torus")->required();
  torus->add_option("minor_radius", "Minor radius of Torus")->required();
  torus->add_option("slices", "Slices of Torus")->required();
  torus->add_option("stacks", "Stacks of Torus")->required();
  torus->add_option("output_file", "File to store the data of Torus surface")
      ->required();

  auto pyramid = app.add_subcommand("pyramid");
  pyramid->add_option("height", "Height of Pyramid")->required();
  pyramid->add_option("slices", "Slices of Pyramid")->required();
  pyramid
      ->add_option("output_file", "File to store the data of Pyramid surface")
      ->required();

  CLI11_PARSE(app, argc, argv);

  auto subcommands = app.get_subcommands();

  for (auto subcommand : subcommands) {
    if (app.got_subcommand(subcommand)) {
      this->figure = fromString(subcommand->get_name());
      this->outFile = subcommand->get_option("output_file")->results().at(0);
      for (auto option : subcommand->get_options()) {
        auto option_name = option->get_name();
        if (option_name != "patches_file" && option_name != "output_file") {
          for (const auto &option_result : option->results()) {
            this->dimensions.push_back(std::stof(option_result));
          }
        }
      }
      auto patch_file = subcommand->get_option_no_throw("patches_file");
      if (patch_file)
        this->inputFile = patch_file->results().at(0);
      break;
    }
  }

  return 0;
}

Figures fromString(std::string_view str) {
  if (str == "sphere") {
    return Figures::Sphere;
  } else if (str == "plane") {
    return Figures::Plane;
  } else if (str == "box") {
    return Figures::Box;
  } else if (str == "cone") {
    return Figures::Cone;
  } else if (str == "torus") {
    return Figures::Torus;
  } else if (str == "pyramid") {
    return Figures::Pyramid;
  } else if (str == "bezzier") {
    return Figures::Bezzier;
  } else {
    throw std::invalid_argument("Invalid figure");
  }
}

// Input::Input(int argc, char *argv[]) {
//   if (argc < 5) {
//     throw std::invalid_argument("Not enough arguments");
//   }
//
//   int begin = 2;
//   this->figure = fromString(argv[1]);
//   if (this->figure == Figures::Bezzier) {
//     this->inputFile = argv[2];
//     begin = 3;
//   }
//   this->outFile = argv[argc - 1];
//
//   for (int i = begin; i < argc - 1; ++i) {
//     dimensions.push_back(std::stof(argv[i]));
//   }
// }

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
  if (this->figure == Figures::Plane) {
    return std::make_unique<Plane>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1])});
  } else if (this->figure == Figures::Box) {
    return std::make_unique<Box>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1])});
  }

  switch (this->figure) {
  case Figures::Plane: {
    return std::make_unique<Plane>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1])});

    break;
  }
  case Figures::Box: {
    return std::make_unique<Box>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1])});
    break;
  }
  case Figures::Sphere: {
    return std::make_unique<Sphere>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1]),
                           static_cast<float>(this->dimensions[2])});
    break;
  }
  case Figures::Cone: {
    return std::make_unique<Cone>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1]),
                           static_cast<float>(this->dimensions[2]),
                           static_cast<float>(this->dimensions[3])});
    break;
  }
  case Figures::Torus: {
    return std::make_unique<Torus>(
        std::vector<float>{static_cast<float>(this->dimensions[0]),
                           static_cast<float>(this->dimensions[1]),
                           static_cast<float>(this->dimensions[2]),
                           static_cast<float>(this->dimensions[3])});
  }
  case Figures::Pyramid: {
    return std::make_unique<Pyramid>(std::vector<float>{
        static_cast<float>(this->dimensions[0]), // height
        static_cast<float>(this->dimensions[1]), // slices
    });
  }
  case Figures::Bezzier: {
    return std::make_unique<Bezzier>(this->inputFile, this->dimensions[0]);
  }
  default:
    return nullptr;
    break;
  }
  return nullptr;
}
}; // namespace input
