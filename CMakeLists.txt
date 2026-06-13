cmake_minimum_required(VERSION 3.18)
project(custom_allocator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
# include module by full path to avoid module path issues in some environments
if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake")
  include("${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake")
else()
  message(WARNING "CompilerWarnings.cmake not found in cmake/ - continuing without custom warning helper")
  function(target_enable_all_warnings target)
	# noop
  endfunction()
endif()

option(ENABLE_BENCHMARKS "Build benchmarks" ON)

if(EXISTS "${CMAKE_SOURCE_DIR}/src/CMakeLists.txt")
  add_subdirectory(src)
else()
  message(WARNING "src/CMakeLists.txt not found; skipping src")
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
  add_subdirectory(tests)
else()
  message(WARNING "tests/CMakeLists.txt not found; skipping tests")
endif()

if(ENABLE_BENCHMARKS AND EXISTS "${CMAKE_SOURCE_DIR}/benchmarks/CMakeLists.txt")
  add_subdirectory(benchmarks)
else()
  if(ENABLE_BENCHMARKS)
	message(WARNING "benchmarks/CMakeLists.txt not found; skipping benchmarks")
  endif()
endif()
