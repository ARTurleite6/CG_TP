#ifndef TORUS_H
#define TORUS_H

#include "figure.h"
class Torus : public Figure {

public:
  explicit Torus(const std::vector<float> &args);

private:
  float raio_maior, raio_menor;
  std::uint32_t number_stacks, number_slices;
};

#endif //  TORUS_H
