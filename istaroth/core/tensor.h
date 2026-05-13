#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "istaroth/core/buffer.h"

namespace istaroth::core {

enum class DType : std::uint8_t {
  kFloat32 = 0,
  kFloat16 = 1,
  kInt32 = 2,
};

class Tensor {
 public:
  Tensor() = default;
  Tensor(std::vector<std::size_t> shape, DType dtype, Buffer buffer);

  [[nodiscard]] const std::vector<std::size_t>& Shape() const { return shape_; }
  [[nodiscard]] DType Type() const { return dtype_; }
  [[nodiscard]] const Buffer& Storage() const { return buffer_; }
  [[nodiscard]] Buffer& Storage() { return buffer_; }

 private:
  std::vector<std::size_t> shape_{};
  DType dtype_{DType::kFloat32};
  Buffer buffer_{};
};

[[nodiscard]] std::size_t DTypeSize(DType type);
[[nodiscard]] std::size_t Numel(const std::vector<std::size_t>& shape);

}  // namespace istaroth::core
