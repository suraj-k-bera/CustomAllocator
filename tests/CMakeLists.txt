enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test_allocator
  test_allocator.cpp
)

target_link_libraries(test_allocator PRIVATE gtest_main custom_allocator)
target_include_directories(test_allocator PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_enable_all_warnings(test_allocator)

include(GoogleTest)
gtest_discover_tests(test_allocator)
