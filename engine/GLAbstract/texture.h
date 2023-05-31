#ifndef TEXTURE_H
#define TEXTURE_H
#include "../include.h"
#include <fmt/format.h>
#include "IL/il.h"
#include "IL/ilu.h"

class Texture {

public:
  explicit Texture(std::string_view file_path);
  Texture(const Texture &) = delete;
  Texture(Texture &&) noexcept;
  ~Texture();

  inline void bind() const noexcept {
    glBindTexture(GL_TEXTURE_2D, this->textureid);
  }
  static inline void unbind() noexcept { glBindTexture(GL_TEXTURE_2D, 0); }

private:
  unsigned int textureid;
};

#endif // TEXTURE_H
