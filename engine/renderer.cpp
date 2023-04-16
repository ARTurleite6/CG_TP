#include "renderer.h"
#include "camera.h"
#include <fstream>
#include <stdexcept>

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

void Renderer::draw(const std::string &file) {
  if (!this->cache.contains(file)) {
    this->parse(file);
  }

  auto [vbo, vertices] = this->cache[file];
  std::cout << "vbo = " << vbo << '\n';

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size() / 3));
}

void Renderer::parse(const std::string &file) {
  if (this->cache.contains(file))
    throw std::invalid_argument("Este ficheiro ja existe na cache");

  std::ifstream file_stream;

  file_stream.open(file);
  if (!file_stream.is_open())
    throw std::invalid_argument("Este ficheiro nao existe");

  std::string buffer;

  CacheEntry cacheEntry;

  while (std::getline(file_stream, buffer)) {

    std::array<std::string_view, 3> vertices = split<3>(buffer, ' ');
    std::array<float, 3> verticesFloat{};
    std::transform(vertices.cbegin(), vertices.cend(), verticesFloat.begin(),
                   [](const std::string_view value) {
                     return std::stof(std::string(value));
                   });

    cacheEntry.vertices.push_back(verticesFloat[0]);
    cacheEntry.vertices.push_back(verticesFloat[1]);
    cacheEntry.vertices.push_back(verticesFloat[2]);
  }

  std::cout << "tam = " << cacheEntry.vertices.size() << '\n';

  glGenBuffers(1, &cacheEntry.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, cacheEntry.vbo);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<long>(sizeof(float) * cacheEntry.vertices.size()),
               cacheEntry.vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  this->cache[file] = std::move(cacheEntry);
}
