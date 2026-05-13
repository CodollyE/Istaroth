#include "istaroth/model/config_loader.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>

namespace istaroth::model {
namespace {

std::string ReadText(const std::string& path) {
  std::ifstream ifs(path);
  if (!ifs) {
    throw std::runtime_error("Failed to open config file: " + path);
  }
  std::ostringstream oss;
  oss << ifs.rdbuf();
  return oss.str();
}

std::size_t ExtractUnsigned(const std::string& content, const std::string& key) {
  const std::regex pattern("\"" + key + "\"\\s*:\\s*([0-9]+)");
  std::smatch match;
  if (std::regex_search(content, match, pattern) && match.size() > 1) {
    return static_cast<std::size_t>(std::stoull(match[1].str()));
  }
  throw std::runtime_error("Missing required Qwen2 config key: " + key);
}

}  // namespace

Qwen2Config LoadQwen2Config(const std::string& config_json_path) {
  const std::string content = ReadText(config_json_path);

  Qwen2Config cfg;
  cfg.hidden_size = ExtractUnsigned(content, "hidden_size");
  cfg.num_attention_heads = ExtractUnsigned(content, "num_attention_heads");
  cfg.num_hidden_layers = ExtractUnsigned(content, "num_hidden_layers");
  cfg.vocab_size = ExtractUnsigned(content, "vocab_size");
  cfg.max_position_embeddings = ExtractUnsigned(content, "max_position_embeddings");
  return cfg;
}

}  // namespace istaroth::model
