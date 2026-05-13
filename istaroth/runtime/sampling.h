#pragma once

#include <cstddef>
#include <vector>

namespace istaroth::runtime {

struct SamplingParams {
  std::size_t top_k{40};
  float top_p{0.95F};
  float temperature{0.8F};
};

int SampleToken(const std::vector<float>& logits, const SamplingParams& params);

}  // namespace istaroth::runtime
