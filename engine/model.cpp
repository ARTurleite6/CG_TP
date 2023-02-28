#include "model.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

template <std::uint32_t N>
std::array<std::string, N> split(std::string_view str, char delimiter) {
  std::array<std::string, N> arr;

  std::size_t pos = 0;
  std::size_t start = 0;
  std::size_t i = 0;
  while ((pos = str.find(delimiter)) != std::string::npos) {
    arr[i++] = str.substr(start, pos);
    start = pos + 1;
  }
  arr[i++] = str.substr(start, pos);

  return arr;
}

Model::Model(std::string_view filename) : filename(filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "File " << filename << " opened successfully" << std::endl;
    return;
  }

  std::string buffer;
  while (std::getline(file, buffer)) {
    std::array<std::string, 3> arr = split<3>(buffer, ' ');

    this->vertices.emplace_back(std::stof(arr[0]), std::stof(arr[1]),
                                std::stof(arr[2]));
  }
}
