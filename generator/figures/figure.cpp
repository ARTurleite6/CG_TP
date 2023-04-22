#include "figure.h"

Figure::Figure(const std::vector<float> &args) {}

void Figure::storeVertices(std::string_view outFile) const noexcept {

  std::ofstream file;
  file.open(outFile.data());
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << outFile << '\n';
  }

  for (const auto &t : triangles) {
    for (const auto &v : t.vertices) {
      file << v.x << " " << v.y << " " << v.z << "\n";
    }
  }
}

void Figure::computeOperation(const Matrix<float, 4, 4> &m) noexcept {
  for (auto &triangle : this->triangles)
    for (auto &v : triangle.vertices) {
      v *= m;
    }
}
