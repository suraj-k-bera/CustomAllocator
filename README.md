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

Build instructions (MSVC, GCC, Clang)
-----------------------------------
Below are example workflows for building this project with MSVC (Visual Studio), GCC, and Clang. The project uses CMake and Ninja in the examples, but you can adapt to other generators if preferred.

MSVC (Visual Studio) - recommended on Windows
- Using Visual Studio IDE: open the repository folder in Visual Studio (File -> Open -> Folder) and use the built-in CMake support. Choose the desired configuration (Debug/Release) and build from the GUI.
- Using Developer PowerShell / Developer Command Prompt:
  1. Open "Developer PowerShell for VS" (sets MSVC environment variables) or run vcvarsall.bat for your toolset.
  2. From the repository root:
	 mkdir build-msvc && cd build-msvc
	 cmake -G Ninja -A x64 -DCMAKE_BUILD_TYPE=Release ..
	 cmake --build . --config Release

  Notes:
  - The -A x64 selects the 64-bit platform. Adjust if you need x86 or ARM.
  - You can also use the Visual Studio generator (for example "Visual Studio 17 2022") if you prefer IDE solutions instead of Ninja:
	cmake -G "Visual Studio 17 2022" -A x64 -S . -B build-vs
	cmake --build build-vs --config Release

GCC (Windows via MinGW-w64 / MSYS2 or WSL)
- MinGW-w64 (MSYS2) on Windows:
  1. Install MSYS2 and the mingw-w64 toolchain and ninja (see MSYS2 docs).
  2. From PowerShell (adjust paths to your MSYS2 installation):
	 cmake -G Ninja -S . -B build-gcc -DCMAKE_C_COMPILER="C:/msys64/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/msys64/mingw64/bin/g++.exe" -DCMAKE_BUILD_TYPE=Release
	 cmake --build build-gcc -- -j

- WSL (Ubuntu) - recommended if you want a native Linux toolchain on Windows:
  1. In WSL install required packages: sudo apt update && sudo apt install build-essential cmake ninja-build
  2. From the project root inside WSL (clone here or access the Windows repo via /mnt):
	 mkdir -p build && cd build
	 cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Release
	 cmake --build . -- -j
	 ctest --output-on-failure

Clang
- Clang with MSVC-compatible driver (clang-cl) on Windows:
  1. Open "Developer PowerShell for VS" so the MSVC environment is available.
  2. From the repository root:
	 mkdir build-clang && cd build-clang
	 cmake -G Ninja -S .. -B . -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_BUILD_TYPE=Release
	 cmake --build . --config Release

- Clang on WSL / Linux:
  1. Install clang and ninja: sudo apt install clang ninja-build
  2. From the project root inside WSL:
	 mkdir build && cd build
	 cmake -G Ninja .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang -DCMAKE_BUILD_TYPE=Release
	 cmake --build . -- -j

Running tests and benchmarks
- Tests are configured with GoogleTest and can be run with CTest from the build directory:
  ctest --output-on-failure
- Or run the test binary directly (e.g., build/tests/tests.exe or build/tests/tests on Linux/WSL).

Troubleshooting
- If CMake picks MSVC by default on Windows and you want a different toolchain, explicitly set CMAKE_C_COMPILER and CMAKE_CXX_COMPILER (as shown above) or run from the appropriate developer shell.
- If FetchContent fails during configure due to network, ensure you have network access or pre-cache dependencies.

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
