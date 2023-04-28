#ifndef RENDERER_H
#define RENDERER_H
#include "my_math.h"
#include "include.h"

struct CacheEntry {
  unsigned int vbo[2];
  std::vector<float> vertices;
  std::vector<float> normals;
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

  void draw(const std::string &file);

private:
  void parse(const std::string &file);

  std::unordered_map<std::string, CacheEntry> cache;
};

#endif // RENDERER_H
