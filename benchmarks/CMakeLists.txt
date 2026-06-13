include(FetchContent)
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.7.1
)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
FetchContent_MakeAvailable(benchmark)

add_executable(bench_allocator
  bench_allocator.cpp
)

target_link_libraries(bench_allocator PRIVATE benchmark::benchmark custom_allocator)
target_include_directories(bench_allocator PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_enable_all_warnings(bench_allocator)
