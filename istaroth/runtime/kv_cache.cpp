#include "istaroth/runtime/kv_cache.h"

#include <algorithm>

namespace istaroth::runtime {

KvCache::KvCache(KvCacheConfig config) : config_(config) {}

void KvCache::Reset() {
  current_tokens_ = 0;
}

void KvCache::Advance(std::size_t tokens) {
  current_tokens_ = std::min(config_.max_seq_len, current_tokens_ + tokens);
}

}  // namespace istaroth::runtime
