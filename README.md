# Istaroth

Initial C++20/CUDA-friendly inference framework skeleton inspired by [zjhellofss/KuiperLLama](https://github.com/zjhellofss/KuiperLLama), with planned Qwen2 support.

## Layout

- `cmake/` CMake modules (reserved)
- `demo/` demo executable (`qwen_infer`)
- `hf_infer/` HuggingFace-side comparison scripts (reserved)
- `istaroth/` core runtime/model/tokenizer abstractions
- `test/` tests (reserved)
- `tools/` model export tooling (`export_qwen2.py`)
- `third_party/` vendored/managed dependencies (reserved)

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/qwen_infer
```

CPU-only build works by default when CUDA compiler is unavailable.

### CMake options

- `USE_CPM` (default `OFF`): reserve CPM-based dependency wiring
- `QWEN2_SUPPORT` (default `ON`): compile with Qwen2 support flag
- `CUDA` (default `ON`): enable CUDA language only if a CUDA compiler is found

## Qwen2 export workflow (placeholder)

The intended flow mirrors KuiperLLama and the llama2.c-style export pattern:

```bash
python3 tools/export_qwen2.py qwen2.bin --hf Qwen/Qwen2-0.5B-Instruct
```

Current script is a placeholder and prints planned steps. TODO: implement HF weight loading + binary emission compatible with Istaroth runtime.
