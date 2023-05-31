#include "texture.h"

Texture::Texture(std::string_view file_path) : textureid(0) {
  int tw, th;
  unsigned int image = 0;
  ilGenImages(1, &image);
  ilBindImage(image);
  if (!ilLoadImage((ILstring)file_path.data())) {
    ILenum error = ilGetError();
    const char *errorMessage = iluGetString(error);
    printf("Error to load image: %s", errorMessage);
  }
  tw = ilGetInteger(IL_IMAGE_WIDTH);
  th = ilGetInteger(IL_IMAGE_HEIGHT);
  ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  auto texData = ilGetData();

  glGenTextures(1, &this->textureid);
  glBindTexture(GL_TEXTURE_2D, this->textureid);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               texData);
  glGenerateMipmap(GL_TEXTURE_2D);

  ilDeleteImages(1, &image);
}

Texture::Texture(Texture &&texture) noexcept : textureid(texture.textureid) {
  texture.textureid = 0;
}

Texture::~Texture() { glDeleteTextures(1, &this->textureid); }
