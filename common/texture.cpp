#include "texture.h"
#include "glad/glad.h"

Texture::Texture(uint32_t width, uint32_t height) {
  glCreateTextures(GL_TEXTURE_2D, 1, &texture_);
  glTextureStorage2D(texture_, 1, GL_RGBA8, width, height);
  SetParameters();
}

Texture::~Texture() {}

void Texture::SetParameters() {
  glTextureParameteri(texture_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(texture_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTextureParameteri(texture_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glGenerateTextureMipmap(texture_);
}

void Texture::Bind(uint32_t unit) { glBindTextureUnit(unit, texture_); }