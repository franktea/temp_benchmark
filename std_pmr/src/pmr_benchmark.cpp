#include <benchmark/benchmark.h>
#include <memory_resource>
#include <vector>
#include <map>

// 传统分配器 - vector基准测试
static void BM_Vector_Default(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> container;
        for (int i = 0; i < state.range(0); ++i) {
            container.push_back(i);
        }
        benchmark::DoNotOptimize(container);
    }
}

// PMR monotonic分配器 - vector基准测试
static void BM_Vector_Monotonic(benchmark::State& state) {
    for (auto _ : state) {
        std::byte buff[4096];
        std::pmr::monotonic_buffer_resource pool(buff, sizeof(buff));
        std::pmr::vector<int> container(&pool);
        for (int i = 0; i < state.range(0); ++i) {
            container.push_back(i);
        }
        benchmark::DoNotOptimize(container);
    }
}

// 传统分配器 - map基准测试
static void BM_Map_Default(benchmark::State& state) {
    for (auto _ : state) {
        std::map<int, int> container;
        for (int i = 0; i < state.range(0); ++i) {
            container[i] = i;
        }
        benchmark::DoNotOptimize(container);
    }
}

// PMR monotonic分配器 - map基准测试
static void BM_Map_Monotonic(benchmark::State& state) {
    for (auto _ : state) {
        std::byte buff[4096];
        std::pmr::monotonic_buffer_resource pool(buff, sizeof(buff));
        std::pmr::map<int, int> container(&pool);
        for (int i = 0; i < state.range(0); ++i) {
            container[i] = i;
        }
        benchmark::DoNotOptimize(container);
    }
}

// 注册基准测试
BENCHMARK(BM_Vector_Default)->RangeMultiplier(2)->Range(1<<10, 1<<16);
BENCHMARK(BM_Vector_Monotonic)->RangeMultiplier(2)->Range(1<<10, 1<<16);
BENCHMARK(BM_Map_Default)->RangeMultiplier(2)->Range(1<<10, 1<<16);
BENCHMARK(BM_Map_Monotonic)->RangeMultiplier(2)->Range(1<<10, 1<<16);

BENCHMARK_MAIN();
