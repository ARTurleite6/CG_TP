#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "input/input.h"
#include "input/utils.h"
#include <array>
#include <cstddef>
#include <fstream>
#include <glm/glm.hpp>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <stdexcept>
#include <type_traits>

int main(int argc, char *argv[]) {

  using namespace input;
  try {

    Input input(argc, argv);
    std::cout << input << '\n';

    auto figure = input.getFigure();

    figure->storeVertices(input.getOutFile());

  } catch (const std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
