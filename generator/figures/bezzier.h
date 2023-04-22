#ifndef BEZZIER_H
#define BEZZIER_H

#include "figure.h"
#include "my_math.h"
#include "matrix.h"
#include "io.h"
class Bezzier: public Figure {
    
    public:

    Bezzier(const std::string &filepath, float tesselation);
    
    void storeVertices(std::string_view outFile) const noexcept override;

    
    private:
    static maths::Vertex getPoint(const matrix::Matrix<Vertex, 4, 4> &mA, float u, float v);

      [[nodiscard]] std::vector<maths::Vertex>
      calculatePoints() const noexcept;
      float tesselation{0.0f};
      std::vector<std::array<int, 16>> patchesIndices{};
      std::vector<maths::Vertex> vertices{};
      };

#endif // BEZZIER_H