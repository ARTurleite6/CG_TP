#include "renderer.h"
#include "camera.h"
#include "io.h"

void Renderer::draw(const std::string &file) {
  if (!this->cache.contains(file)) {
    this->parse(file);
  }

  auto [vbo, vertices, normals] = this->cache[file];

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glVertexPointer(3, GL_FLOAT, 0, nullptr);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size() / 3));

  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glNormalPointer(GL_FLOAT, 0, nullptr);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size() / 3));

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
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

    std::array<std::string_view, 6> vertices = split_N<6>(buffer, " ");
    std::array<float, 6> verticesFloat{};
    std::transform(vertices.cbegin(), vertices.cend(), verticesFloat.begin(),
                   [](const std::string_view value) {
                     return std::stof(std::string(value));
                   });

    cacheEntry.vertices.push_back(verticesFloat[0]);
    cacheEntry.vertices.push_back(verticesFloat[1]);
    cacheEntry.vertices.push_back(verticesFloat[2]);

    cacheEntry.normals.push_back(verticesFloat[3]);
    cacheEntry.normals.push_back(verticesFloat[4]);
    cacheEntry.normals.push_back(verticesFloat[5]);
  }

  glGenBuffers(1, cacheEntry.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, cacheEntry.vbo[0]);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<long>(sizeof(float) * cacheEntry.vertices.size()),
               cacheEntry.vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, cacheEntry.vbo[1]);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<long>(sizeof(float) * cacheEntry.normals.size()),
               cacheEntry.normals.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  this->cache[file] = std::move(cacheEntry);
}
