#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>

class Texture {
public:
  Texture(uint32_t width, uint32_t height);
  ~Texture();

  void Bind(uint32_t unit);

  uint32_t GetID() const { return texture_; }

private:
  void SetParameters();

private:
  uint32_t texture_;
};

#endif // TEXTURE_H