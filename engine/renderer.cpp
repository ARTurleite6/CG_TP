#include "renderer.h"
#include "camera.h"
#include "io.h"

void Renderer::parse_texture(const std::string &tex_file) {
  if (this->cache_textures.contains(tex_file))
    throw std::invalid_argument("Este ficheiro ja existe na cache");

  this->cache_textures.emplace(tex_file, Texture{tex_file});
}

void Renderer::draw(const std::string &file,
                    const std::optional<std::string> &file_tex) {
  if (!this->cache_vertex.contains(file))
    this->parse_vertex(file);

  if (file_tex && !this->cache_textures.contains(file_tex.value())) {
    this->parse_texture(file_tex.value());
  }

  auto &[vertex, normals, tex] = this->cache_vertex.at(file);

  const Texture *texture = nullptr;

  if (file_tex) {
    texture = &this->cache_textures.at(file_tex.value());
    texture->bind();
  }

  vertex.bind();
  VBO::setVertexLayout();

  normals.bind();
  VBO::setNormalLayout();
  // glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  // glNormalPointer(GL_FLOAT, 0, nullptr);

  // glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size() / 3));
  tex.bind();
  VBO::setTexCoordLayout();
  vertex.draw();

  if (texture)
    Texture::unbind();
}

void Renderer::parse_vertex(const std::string &file) {
  if (this->cache_vertex.contains(file))
    throw std::invalid_argument("Este ficheiro ja existe na cache");

  std::ifstream file_stream;

  file_stream.open(file);
  if (!file_stream.is_open())
    throw std::invalid_argument("Este ficheiro nao existe");

  std::string buffer;

  std::vector<float> vertex;
  std::vector<float> normals;
  std::vector<float> texCoords;

  while (std::getline(file_stream, buffer)) {

    std::array<std::string_view, 8> vertices = split_N<8>(buffer, " ");
    std::array<float, 8> verticesFloat{};
    std::transform(vertices.cbegin(), vertices.cend(), verticesFloat.begin(),
                   [](const std::string_view value) {
                     return std::stof(std::string(value));
                   });

    vertex.push_back(verticesFloat[0]);
    vertex.push_back(verticesFloat[1]);
    vertex.push_back(verticesFloat[2]);

    normals.push_back(verticesFloat[3]);
    normals.push_back(verticesFloat[4]);
    normals.push_back(verticesFloat[5]);

    texCoords.push_back(verticesFloat[6]);
    texCoords.push_back(verticesFloat[7]);
  }

  //  glGenBuffers(2, cacheEntry.vbo);
  //  glBindBuffer(GL_ARRAY_BUFFER, cacheEntry.vbo[0]);
  //  glBufferData(GL_ARRAY_BUFFER,
  //               static_cast<long>(sizeof(float) *
  //               cacheEntry.vertices.size()), cacheEntry.vertices.data(),
  //               GL_STATIC_DRAW);

  //  glBindBuffer(GL_ARRAY_BUFFER, cacheEntry.vbo[1]);
  //  glBufferData(GL_ARRAY_BUFFER,
  //               static_cast<long>(sizeof(float) * cacheEntry.normals.size()),
  //               cacheEntry.normals.data(), GL_STATIC_DRAW);
  //
  //  glBindBuffer(GL_ARRAY_BUFFER, 0);
  for(const auto &normal : normals)
      std::cout << normal << '\n';
  this->cache_vertex.emplace(
      std::string(file), CacheEntry{VBO{vertex}, VBO{normals}, VBO{texCoords}});

  // this->cache_vertex[file] =
  //     CacheEntry{std::move(vertex), std::move(normals),
  //     std::move(texCoords)};
}
