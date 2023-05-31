#ifndef VBO_H
#define VBO_H
#include "../include.h"

class VBO {

public:
  explicit VBO(const std::vector<float> &vertex);
  VBO(const VBO &vbo) = delete;
  VBO(VBO &&vbo) noexcept;
  ~VBO();

  inline void bind() const noexcept {
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  }

  static inline void unbind() noexcept { glBindBuffer(GL_ARRAY_BUFFER, 0); }

  static inline void setVertexLayout() {
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
  }

  static inline void setTexCoordLayout() {
    glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
  }

  static inline void setNormalLayout() {
    glNormalPointer(GL_FLOAT, 0, nullptr);
  }

  inline void draw() const {
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(this->vertex_count));
  }

private:
  unsigned int vbo;
  unsigned long vertex_count;
};

#endif // VBO_H
