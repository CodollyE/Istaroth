#include "istaroth/runtime/sampling.h"

#include <algorithm>

namespace istaroth::runtime {

int SampleToken(const std::vector<float>& logits, const SamplingParams& params) {
  (void)params;
  if (logits.empty()) {
    return -1;
  }
  return static_cast<int>(
      std::distance(logits.begin(), std::max_element(logits.begin(), logits.end())));
}

}  // namespace istaroth::runtime
