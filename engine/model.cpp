#include "model.h"
#include <GLUT/glut.h>

template <std::uint32_t N>
std::array<std::string_view, N> split(std::string_view str, char delimiter) {
  std::array<std::string_view, N> arr;

  std::size_t pos = 0;
  std::size_t start = 0;
  std::size_t i = 0;
  while (i < N && (pos = str.find(delimiter, start)) != std::string::npos) {
    arr[i] = str.substr(start, pos - start);
    i++;
    start = pos + 1;
  }
  if (start != std::string::npos && i < N)
    arr[i++] = str.substr(start, pos);

  return arr;
}

Model::Model(std::string_view filename) : filename(filename) {
  std::ifstream file;
  file.open(filename.data());
  if (!file.is_open()) {
    std::cerr << "Couldn't open " << filename << " successfully\n";
    return;
  }

  std::string buffer;
  while (std::getline(file, buffer)) {
    std::cout << buffer << '\n';
    std::array<std::string_view, 3> arr = split<3>(buffer, ' ');

    this->vertices.emplace_back(std::stof(std::string(arr[0])),
                                std::stof(std::string(arr[1])),
                                std::stof(std::string(arr[2])));
  }
}

void Model::draw() const noexcept {
  for (const auto &coord : this->vertices) {
    glVertex3f(coord.x, coord.y, coord.z);
  }
}
