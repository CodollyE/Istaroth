#pragma once

#include <cstddef>
#include <memory>

#include "istaroth/core/allocator.h"

namespace istaroth::core {

class Buffer {
 public:
  Buffer() = default;
  Buffer(std::size_t bytes, std::shared_ptr<Allocator> allocator);

  Buffer(const Buffer&) = delete;
  Buffer& operator=(const Buffer&) = delete;

  Buffer(Buffer&& other) noexcept;
  Buffer& operator=(Buffer&& other) noexcept;

  ~Buffer();

  [[nodiscard]] void* Data() const { return data_; }
  [[nodiscard]] std::size_t Size() const { return bytes_; }

 private:
  std::size_t bytes_{0};
  void* data_{nullptr};
  std::shared_ptr<Allocator> allocator_{};
};

}  // namespace istaroth::core
