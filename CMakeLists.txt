cmake_minimum_required(VERSION 3.0)

project(cache)

set(CMAKE_CXX_STANDARD 20)

include_directories(include/)

set (HEADERS include/lfu_cache.hpp)
set (SOURCES src/main.cpp src/lfu_cache.cpp)

add_executable (lfu src/lfu.cpp include/lfu_cache.hpp)
add_executable (perfect src/perfect.cpp include/perfect_cache.hpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(cache_test include/cache_test.hpp src/cache_test.cpp src/run_binary_test.cpp)
target_link_libraries(
    cache_test
  GTest::gtest_main
)
