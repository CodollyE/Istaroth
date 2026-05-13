#include "istaroth/core/buffer.h"

#include <utility>

namespace istaroth::core {

Buffer::Buffer(std::size_t bytes, std::shared_ptr<Allocator> allocator)
    : bytes_(bytes), allocator_(std::move(allocator)) {
  if (bytes_ > 0 && allocator_) {
    data_ = allocator_->Allocate(bytes_);
  }
}

Buffer::Buffer(Buffer&& other) noexcept
    : bytes_(other.bytes_), data_(other.data_), allocator_(std::move(other.allocator_)) {
  other.bytes_ = 0;
  other.data_ = nullptr;
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  if (data_ && allocator_) {
    allocator_->Deallocate(data_);
  }

  bytes_ = other.bytes_;
  data_ = other.data_;
  allocator_ = std::move(other.allocator_);

  other.bytes_ = 0;
  other.data_ = nullptr;
  return *this;
}

Buffer::~Buffer() {
  if (data_ && allocator_) {
    allocator_->Deallocate(data_);
  }
}

}  // namespace istaroth::core
