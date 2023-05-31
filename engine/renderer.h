#ifndef RENDERER_H
#define RENDERER_H
#include "GLAbstract/VBO.h"
#include "GLAbstract/texture.h"
#include "include.h"
#include "my_math.h"

struct CacheEntry {
  CacheEntry(VBO &&vertex, VBO &&normals, VBO &&texCoords)
      : vertex(std::move(vertex)), normals(std::move(normals)),
        texCoords(std::move(texCoords)) {}

  CacheEntry(CacheEntry &c) = delete;
  CacheEntry(CacheEntry &&c) = default;

  VBO vertex, normals, texCoords;
};

// singleton class
class Renderer {
public:
  Renderer() = default;
  Renderer(Renderer &&) = delete;
  Renderer(const Renderer &) = delete;
  Renderer &operator=(Renderer &&) = delete;
  Renderer &operator=(const Renderer &) = delete;
  ~Renderer() = default;

  void draw(const std::string &file,
            const std::optional<std::string> &file_tex = std::nullopt);

private:
  void parse_vertex(const std::string &file);
  void parse_texture(const std::string &tex_file);

  std::unordered_map<std::string, CacheEntry> cache_vertex;
  std::unordered_map<std::string, Texture> cache_textures;
};

#endif // RENDERER_H
