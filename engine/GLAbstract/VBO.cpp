#include "VBO.h"

VBO::VBO(const std::vector<float> &vertex) : vbo(0) {
  std::cout << "constructing vbo\n";
  glGenBuffers(1, &this->vbo);
  this->bind();
  glBufferData(GL_ARRAY_BUFFER, static_cast<int>(sizeof(float) * vertex.size()),
               vertex.data(), GL_STATIC_DRAW);
  this->vertex_count = vertex.size() / 3;
}

VBO::VBO(VBO &&vbo) noexcept : vbo(vbo.vbo), vertex_count(vbo.vertex_count) {
  vbo.vbo = 0;
  vbo.vertex_count = 0;
}

VBO::~VBO() {
  std::cout << "Destroyed VBO\n";
  glDeleteBuffers(1, &this->vbo);
}
