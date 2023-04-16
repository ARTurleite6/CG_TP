#include "engine.h"

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  Engine engine(argv[1]);

  --argc;
  ++argv;

  engine.run(argc, argv);

  return 0;
}
