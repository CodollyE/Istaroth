cmake_minimum_required(VERSION 3.20)

project(Istaroth LANGUAGES CXX)

option(USE_CPM "Use CPM.cmake for dependency management" OFF)
option(QWEN2_SUPPORT "Enable planned Qwen2 support" ON)
option(CUDA "Enable CUDA backend when compiler is available" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CheckLanguage)
set(ISTAROTH_HAS_CUDA OFF)
if(CUDA)
  check_language(CUDA)
  if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
    set(ISTAROTH_HAS_CUDA ON)
  else()
    message(STATUS "CUDA requested, but no CUDA compiler found. Building CPU-only skeleton.")
  endif()
endif()

add_library(istaroth STATIC
  istaroth/core/allocator.cpp
  istaroth/core/buffer.cpp
  istaroth/core/tensor.cpp
  istaroth/model/config_loader.cpp
  istaroth/tokenizer/tokenizer.cpp
  istaroth/runtime/kv_cache.cpp
  istaroth/runtime/sampling.cpp
)

target_include_directories(istaroth
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(istaroth PUBLIC cxx_std_20)

target_compile_definitions(istaroth
  PUBLIC
    ISTAROTH_QWEN2_SUPPORT=$<BOOL:${QWEN2_SUPPORT}>
    ISTAROTH_HAS_CUDA=$<BOOL:${ISTAROTH_HAS_CUDA}>
)

add_executable(qwen_infer demo/qwen_infer.cpp)
target_link_libraries(qwen_infer PRIVATE istaroth)

install(TARGETS istaroth qwen_infer)
