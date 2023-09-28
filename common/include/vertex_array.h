#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "buffer.h"

class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void SetLayout();
  void SetVertexBuffer(const Buffer &buffer);
  void Bind();

private:
  uint32_t vertex_array_{0};
};

#endif // VERTEX_ARRAY_H