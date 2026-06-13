Custom Allocator library (C++23)
================================

Overview
--------
This project provides a small custom allocator library for C++23 that exposes a std::pmr::memory_resource-derived implementation (CustomMemoryResource) and a lightweight header-only polymorphic allocator adaptor. The library target is named custom_allocator and headers live under include/allocator. The implementation files are under src. Unit tests use GoogleTest and benchmarks use GoogleBenchmark (both fetched with CMake FetchContent).

Key features
- C++23 library target: custom_allocator
- Public headers: include/allocator
- Implementation: src
- Unit tests: tests (GTest)
- Benchmarks: benchmarks (GoogleBenchmark)

Prerequisites
- CMake >= 3.18
- A C++23-capable compiler (MSVC, GCC, or Clang)
- Ninja is recommended as the generator but any supported generator is fine
- Network access for FetchContent (GoogleTest / GoogleBenchmark) during configure

Quick build (Ninja)
1. mkdir build && cd build
2. cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
3. cmake --build . --config Release

Run tests
- From the build directory: ctest --output-on-failure
  or run the test executable created under build/tests/

Run benchmarks
- If ENABLE_BENCHMARKS=ON (default), the benchmark executable is created under build/benchmarks/. Run it directly.

Integration
- Add_subdirectory method (recommended for source-level integration):
  - In your project's CMakeLists.txt add:
	add_subdirectory(path/to/CustomAllocator)
	target_link_libraries(your_target PRIVATE custom_allocator)

- FetchContent method (recommended for external project dependency):
  - Use FetchContent to pull this repository and call add_subdirectory on the fetched source; then link custom_allocator to your target.

Usage example (minimal)
Include the public header and use the memory resource / allocator:

	#include "allocator/memory_resource.h"
	#include "allocator/allocator.h"
	#include <vector>

	allocator::CustomMemoryResource mr;
	std::pmr::polymorphic_allocator<int> pa(&mr);
	std::pmr::vector<int> v(pa);
	v.push_back(1);

Notes
- This repository provides a small, extensible starting point. For production use you may want to add platform-specific tuning, more test coverage, install/export rules, and CI configuration.
