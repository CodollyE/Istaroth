#pragma once

#include <cstddef>
#include <string>

namespace istaroth::model {

struct Qwen2Config {
  std::size_t hidden_size{0};
  std::size_t num_attention_heads{0};
  std::size_t num_hidden_layers{0};
  std::size_t vocab_size{0};
  std::size_t max_position_embeddings{0};
};

Qwen2Config LoadQwen2Config(const std::string& config_json_path);

}  // namespace istaroth::model
