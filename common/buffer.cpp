#include "buffer.h"
#include "glad/glad.h"

Buffer::Buffer(uint32_t size) {
  glCreateBuffers(1, &buffer_);
  glNamedBufferStorage(buffer_, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
}

Buffer::~Buffer() {
  if (buffer_) {
    glDeleteBuffers(1, &buffer_);
  }
}