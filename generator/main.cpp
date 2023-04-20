#include "input/input.h"
#include "my_math.h"

int main(int argc, char *argv[]) {

  using namespace input;
  try {

    Input input(argc, argv);

    auto figure = input.getFigure();

    figure->storeVertices(input.getOutFile());

  } catch (const std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
