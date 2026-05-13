#include "istaroth/core/tensor.h"

#include <numeric>
#include <stdexcept>

namespace istaroth::core {

Tensor::Tensor(std::vector<std::size_t> shape, DType dtype, Buffer buffer)
    : shape_(std::move(shape)), dtype_(dtype), buffer_(std::move(buffer)) {}

std::size_t DTypeSize(DType type) {
  switch (type) {
    case DType::kFloat32:
      return 4;
    case DType::kFloat16:
      return 2;
    case DType::kInt32:
      return 4;
    default:
      throw std::invalid_argument("Unsupported tensor dtype");
  }
}

std::size_t Numel(const std::vector<std::size_t>& shape) {
  if (shape.empty()) {
    return 1;
  }
  return std::accumulate(shape.begin(), shape.end(), std::size_t{1},
                         [](std::size_t left, std::size_t right) { return left * right; });
}

}  // namespace istaroth::core
