#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "istaroth/core/allocator.h"
#include "istaroth/core/buffer.h"
#include "istaroth/core/tensor.h"
#include "istaroth/model/config_loader.h"
#include "istaroth/runtime/kv_cache.h"
#include "istaroth/runtime/sampling.h"
#include "istaroth/tokenizer/tokenizer.h"

namespace {

void EnsurePlaceholderFile(const std::filesystem::path& path, const std::string& content) {
  if (std::filesystem::exists(path)) {
    return;
  }

  std::ofstream ofs(path);
  ofs << content;
}

}  // namespace

int main() {
  const auto cwd = std::filesystem::current_path();
  const auto config_path = cwd / "qwen2_config.json";
  const auto tokenizer_path = cwd / "tokenizer.json";

  EnsurePlaceholderFile(config_path,
                        R"({"hidden_size":896,"num_attention_heads":14,"num_hidden_layers":24,"vocab_size":151936,"max_position_embeddings":32768})");
  EnsurePlaceholderFile(tokenizer_path, R"({"version":"placeholder"})");

  const auto config = istaroth::model::LoadQwen2Config(config_path.string());

  istaroth::tokenizer::Tokenizer tokenizer;
  if (!tokenizer.LoadFromJson(tokenizer_path.string())) {
    std::cerr << "Failed to load tokenizer json from: " << tokenizer_path << '\n';
    return 1;
  }

  auto allocator = std::make_shared<istaroth::core::CpuAllocator>();
  const std::vector<std::size_t> shape{1, 16};
  const std::size_t bytes =
      istaroth::core::Numel(shape) * istaroth::core::DTypeSize(istaroth::core::DType::kFloat32);
  istaroth::core::Buffer input_buffer(bytes, allocator);
  istaroth::core::Tensor input_tensor(shape, istaroth::core::DType::kFloat32,
                                      std::move(input_buffer));

  if (config.num_attention_heads == 0 || config.hidden_size % config.num_attention_heads != 0) {
    throw std::runtime_error(
        "Invalid Qwen2 config: hidden_size must be divisible by num_attention_heads");
  }

  istaroth::runtime::KvCache cache({
      .num_layers = config.num_hidden_layers,
      .num_kv_heads = config.num_attention_heads,
      .head_dim = config.hidden_size / config.num_attention_heads,
      .max_seq_len = config.max_position_embeddings,
  });
  cache.Advance(shape.back());

  const auto tokens = tokenizer.Encode("Hello Qwen2");
  const int sampled = istaroth::runtime::SampleToken({0.1F, 0.2F, 0.4F, 0.3F}, {});

  std::cout << "Istaroth Qwen2 skeleton demo\n";
  std::cout << "QWEN2_SUPPORT=" << ISTAROTH_QWEN2_SUPPORT
            << ", HAS_CUDA=" << ISTAROTH_HAS_CUDA << '\n';
  std::cout << "hidden_size=" << config.hidden_size << ", layers=" << config.num_hidden_layers
            << ", vocab=" << config.vocab_size << '\n';
  std::cout << "encoded_tokens=" << tokens.size()
            << ", kv_tokens=" << cache.CurrentTokens() << '\n';
  std::cout << "input_tensor_bytes=" << input_tensor.Storage().Size() << '\n';
  std::cout << "stub_output_token_id=" << sampled << " (TODO: real Qwen2 decode path)\n";

  return 0;
}
