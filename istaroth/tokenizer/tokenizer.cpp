#include "istaroth/tokenizer/tokenizer.h"

#include <fstream>
#include <sstream>

namespace istaroth::tokenizer {

bool Tokenizer::LoadFromJson(const std::string& tokenizer_json_path) {
  std::ifstream ifs(tokenizer_json_path);
  if (!ifs) {
    return false;
  }

  std::ostringstream oss;
  oss << ifs.rdbuf();
  const std::string content = oss.str();
  if (content.find('{') == std::string::npos || content.find('}') == std::string::npos) {
    return false;
  }

  tokenizer_json_path_ = tokenizer_json_path;
  return true;
}

std::vector<int> Tokenizer::Encode(const std::string& text) const {
  // TODO: Replace this placeholder character-level encoding with Qwen2 tokenizer.json BPE.
  std::vector<int> ids;
  ids.reserve(text.size());
  for (unsigned char c : text) {
    ids.push_back(static_cast<int>(c));
  }
  return ids;
}

std::string Tokenizer::Decode(const std::vector<int>& token_ids) const {
  std::string out;
  out.reserve(token_ids.size());
  for (int id : token_ids) {
    out.push_back(static_cast<char>(id));
  }
  return out;
}

}  // namespace istaroth::tokenizer
