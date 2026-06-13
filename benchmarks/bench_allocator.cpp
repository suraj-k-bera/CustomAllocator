#include "allocator/memory_resource.h"
#include "allocator/allocator.h"

#include <benchmark/benchmark.h>
#include <vector>

using namespace allocator;

static void BM_VectorPushBack(benchmark::State& state) {
	CustomMemoryResource mr;
	std::pmr::polymorphic_allocator<int> pa(&mr);
	for (auto _ : state) {
		std::pmr::vector<int> v(pa);
		for (int i = 0; i < 1000; ++i) v.push_back(i);
		benchmark::ClobberMemory();
	}
}
BENCHMARK(BM_VectorPushBack);

BENCHMARK_MAIN();
