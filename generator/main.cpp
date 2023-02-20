#include "input/input.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {

  using namespace input;
  try {
    Input input(argc, argv);
    std::cout << input << '\n';
  } catch (const std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
