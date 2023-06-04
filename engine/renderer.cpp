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
                     try {
                       return std::stof(std::string(value));
                     } catch (std::exception &e) {
                       std::cout << "Error value: " << value << '\n';
                       std::cout << "Error: " << e.what();
                       return 0.0f;
                     }
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

  this->cache_vertex.emplace(
      std::string(file), CacheEntry{VBO{vertex}, VBO{normals}, VBO{texCoords}});
}
