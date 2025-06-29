cmake_minimum_required(VERSION 3.14)
project(pmr_benchmark)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 使用FetchContent获取Google Benchmark
include(FetchContent)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.4
)
set(BENCHMARK_ENABLE_GTEST_TESTS FALSE)
FetchContent_MakeAvailable(googlebenchmark)

# 添加可执行文件
add_executable(pmr_benchmark src/pmr_benchmark.cpp)

# 链接Google Benchmark库
target_link_libraries(pmr_benchmark PRIVATE benchmark::benchmark)
