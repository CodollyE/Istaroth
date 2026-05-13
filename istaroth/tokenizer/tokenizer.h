#pragma once

#include <string>
#include <vector>

namespace istaroth::tokenizer {

class Tokenizer {
 public:
  bool LoadFromJson(const std::string& tokenizer_json_path);

  [[nodiscard]] std::vector<int> Encode(const std::string& text) const;
  [[nodiscard]] std::string Decode(const std::vector<int>& token_ids) const;

 private:
  std::string tokenizer_json_path_{};
};

}  // namespace istaroth::tokenizer
