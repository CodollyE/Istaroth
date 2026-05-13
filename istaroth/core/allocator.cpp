#include "istaroth/core/allocator.h"

#include <new>

namespace istaroth::core {

void* CpuAllocator::Allocate(std::size_t bytes) {
  return ::operator new(bytes);
}

void CpuAllocator::Deallocate(void* ptr) {
  ::operator delete(ptr);
}

}  // namespace istaroth::core
