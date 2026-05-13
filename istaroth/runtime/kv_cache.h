#pragma once

#include <cstddef>

namespace istaroth::runtime {

struct KvCacheConfig {
  std::size_t num_layers{0};
  std::size_t num_kv_heads{0};
  std::size_t head_dim{0};
  std::size_t max_seq_len{0};
};

class KvCache {
 public:
  explicit KvCache(KvCacheConfig config);

  void Reset();
  void Advance(std::size_t tokens);

  [[nodiscard]] std::size_t CurrentTokens() const { return current_tokens_; }
  [[nodiscard]] const KvCacheConfig& Config() const { return config_; }

 private:
  KvCacheConfig config_{};
  std::size_t current_tokens_{0};
};

}  // namespace istaroth::runtime
