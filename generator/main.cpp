#include "input/input.h"
#include "my_math.h"
#include <CLI/CLI.hpp>

int main(int argc, char *argv[]) {

    input::Input input(argc, argv);

  //CLI::App app{"Generator"};

  //auto plane = app.add_subcommand("plane")->required();
  //plane->add_option("length", "Length of the plane")->required();
  //plane->add_option("divisions", "Divisions of the plane")->required();
  //plane->add_option("output_file", "File to store the data of plane")
  //    ->required();

  //auto box = app.add_subcommand("box");
  //box->add_option("length", "Length of the box")->required();
  //box->add_option("divisions", "Divisions of the box")->required();
  //box->add_option("output_file", "File to store the data of box")->required();

  //auto sphere = app.add_subcommand("sphere");
  //sphere->add_option("radius", "Radius of the sphere")->required();
  //sphere->add_option("slices", "Slices of the sphere")->required();
  //sphere->add_option("stacks", "Stacks of sphere")->required();
  //sphere->add_option("output_file", "File to store the data of sphere")
  //    ->required();

  //auto cone = app.add_subcommand("cone");
  //cone->add_option("radius", "Radius of the cone")->required();
  //cone->add_option("height", "Height of the cone")->required();
  //cone->add_option("slices", "Slices of cone")->required();
  //cone->add_option("stacks", "Stacks of cone")->required();
  //cone->add_option("output_file", "File to store the data of cone")->required();

  //auto bezzier = app.add_subcommand("bezzier");
  //bezzier
  //    ->add_option("patches_file",
  //                 "File with bezzier patches and control points")
  //    ->required();
  //bezzier->add_option("tesselation", "Tesselation to be used")->required();
  //bezzier
  //    ->add_option("output_file", "File to store the data of bezzier surface")
  //    ->required();

  //auto torus = app.add_subcommand("torus");
  //torus->add_option("major_radius", "Major radius of Torus")->required();
  //torus->add_option("minor_radius", "Minor radius of Torus")->required();
  //torus->add_option("slices", "Slices of Torus")->required();
  //torus->add_option("stacks", "Stacks of Torus")->required();
  //torus->add_option("output_file", "File to store the data of Torus surface")
  //    ->required();

  //auto pyramid = app.add_subcommand("pyramid");
  //pyramid->add_option("height", "Height of Pyramid")->required();
  //pyramid->add_option("slices", "Slices of Pyramid")->required();
  //pyramid->add_option("output_file", "File to store the data of Pyramid surface")
  //    ->required();

  //CLI11_PARSE(app, argc, argv);

    auto figure = input.getFigure();
    if(figure)
        figure->storeVertices(input.getOutFile());

  //  using namespace input;
  //  try {
  //
  //    Input input(argc, argv);
  //
  //    auto figure = input.getFigure();
  //
  //    figure->storeVertices(input.getOutFile());
  //
  //  } catch (const std::invalid_argument &e) {
  //    std::cout << e.what() << std::endl;
  //  }

  return 0;
}
