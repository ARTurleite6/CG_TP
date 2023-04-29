#include "figure.h"

Figure::Figure(const std::vector<float> &args) {}

void Figure::storeVertices(std::string_view outFile) const noexcept {

  std::ofstream file;
  file.open(outFile.data());
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << outFile << '\n';
  }

  auto point = 0;
  for (const auto &v : this->vertices) {
    auto normal = this->normals[point++];
    file << v.x << ' ' << v.y << ' ' << v.z << ' ' << normal.x << ' '
         << normal.y << ' ' << normal.z << '\n';
  }
}

void Figure::computeOperation(const Matrix<float, 4, 4> &m) noexcept {
  auto point = 0;
  for (auto &v : this->vertices) {
    v = m * v;
  }
}
