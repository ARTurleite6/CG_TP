#include "input/input.h"
#include "my_math.h"
#include <CLI/CLI.hpp>

int main(int argc, char *argv[]) {

  input::Input input(argc, argv);
  auto figure = input.getFigure();
  if (figure)
    figure->storeVertices(input.getOutFile());

  return 0;
}
