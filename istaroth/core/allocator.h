#pragma once

#include <cstddef>

namespace istaroth::core {

class Allocator {
 public:
  virtual ~Allocator() = default;
  virtual void* Allocate(std::size_t bytes) = 0;
  virtual void Deallocate(void* ptr) = 0;
};

class CpuAllocator final : public Allocator {
 public:
  void* Allocate(std::size_t bytes) override;
  void Deallocate(void* ptr) override;
};

}  // namespace istaroth::core
