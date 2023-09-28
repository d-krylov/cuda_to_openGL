#ifndef BUFFER_H
#define BUFFER_H

#include <cstdint>

class Buffer {
public:
  Buffer(uint32_t size);
  ~Buffer();

  uint32_t GetID() const { return buffer_; }

private:
  uint32_t buffer_{0};
};

#endif // BUFFER_H