#include "vertex_array.h"
#include "glad/glad.h"

VertexArray::VertexArray() { glCreateVertexArrays(1, &vertex_array_); }

VertexArray::~VertexArray() {
  if (vertex_array_) {
    glDeleteVertexArrays(1, &vertex_array_);
  }
}

void VertexArray::SetLayout() {
  glEnableVertexArrayAttrib(vertex_array_, 0);
  glVertexArrayAttribFormat(vertex_array_, 0, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vertex_array_, 0, 0);

  glEnableVertexArrayAttrib(vertex_array_, 1);
  glVertexArrayAttribFormat(vertex_array_, 1, 3, GL_FLOAT, GL_FALSE, 8);
  glVertexArrayAttribBinding(vertex_array_, 1, 0);
}

void VertexArray::SetVertexBuffer(const Buffer &buffer) {
  glVertexArrayVertexBuffer(vertex_array_, 0, buffer.GetID(), 0, 20);
}

void VertexArray::Bind() { glBindVertexArray(vertex_array_); }
